#include "Editor.hpp"
#include "Math.hpp"

#define TABSTOP 8
#define EMPTY_LINE '~'

Editor::Editor(WINDOW* mainWindow):
_mainWindow { mainWindow },
_verticalScroll { getmaxy(mainWindow) }
//_horizontalScroll { getmaxx(mainWindow) }
{}

void Editor::refresh(){
	wrefresh(_mainWindow);
}

void Editor::renderFile() {
	int lastRow = getmaxy(_mainWindow);
	for(int i = 0; i < lastRow; i++) {
		renderRow(i);
	}
	moveToChar(_lineIndex, _charIndex);
}

void Editor::moveUp(){
	moveToChar(_lineIndex - 1, _charIndex);
}

void Editor::moveDown(){
	moveToChar(_lineIndex+1, _charIndex);
}

void Editor::moveLeft(){
	moveToChar(_lineIndex, _charIndex-1);
}

void Editor::moveRight(){
	moveToChar(_lineIndex, _charIndex+1);
}

void Editor::moveToStartOfFile(){
	moveToChar(0, 0);
}

void Editor::moveToEndOfFile(){
	int lastLineIndex = _currentFile->lineCount() - 1;
	std::string lastLine = _currentFile->getLine(lastLineIndex);
	moveToChar(lastLineIndex, lastLine.length());
}

void Editor::moveToStartOfLine(){
	moveToChar(_lineIndex, 0);
}

void Editor::moveToEndOfLine(){
	std::string line = _currentFile->getLine(_lineIndex);
	moveToChar(_lineIndex, line.length());
}

void Editor::moveToLine(int lineIndex){
	lineIndex = clamp(lineIndex, 0, _currentFile->lineCount() - 1);
	_lineIndex = lineIndex;
	// Handle scrolling
	int firstLineShown = _verticalScroll.getStart();
	int lastLineShown = _verticalScroll.getEnd() - 1;
	if(_lineIndex < firstLineShown){
		_verticalScroll.move(_lineIndex - firstLineShown);
	} else if(_lineIndex > lastLineShown) {
		_verticalScroll.move(_lineIndex - lastLineShown);
	}

	// Move
	int row = _lineIndex - _verticalScroll.getStart();
	wmove(_mainWindow, row, getcurx(_mainWindow));
}

void Editor::moveToChar(int lineIndex, int charIndex){
	_verticalScroll.setContentSize(_currentFile->lineCount());

	moveToLine(lineIndex);

	// We need the line string for the col computation
	std::string line = _currentFile->getLine(_lineIndex);
	_charIndex = clamp(charIndex, 0, line.length());
	int col = 0;
	for(int i = 0; i < line.length() && i < _charIndex; i++) {
		if(line[i] == '\t'){
			col += TABSTOP - (col % TABSTOP);
		} else {
			col++;
		}
	}

	wmove(_mainWindow, getcury(_mainWindow), col);
}

void Editor::insertChar(char c){
	std::string line = _currentFile->getLine(_lineIndex);
	line.insert(_charIndex, 1, c);
	_currentFile->editLine(_lineIndex, line);
	moveRight();
	//moveToChar(_lineIndex, _charIndex + 1);
}

void Editor::insertNewLine(){
	std::string line = _currentFile->getLine(_lineIndex);

	std::string firstHalf = line.substr(0, _charIndex);
	std::string secondHalf = line.substr(_charIndex);

	_currentFile->insertLine(_lineIndex);
	_currentFile->editLine(_lineIndex, firstHalf);
	_currentFile->editLine(_lineIndex+1, secondHalf);
	moveDown();
	moveToStartOfLine();
}

void Editor::eraseBackward(){
	std::string line = _currentFile->getLine(_lineIndex);

	if(_charIndex == 0 && _lineIndex > 0){
		// Remove line feed
		std::string previousLine = _currentFile->getLine(_lineIndex - 1);
		_currentFile->editLine(_lineIndex - 1, previousLine + line);
		_currentFile->removeLine(_lineIndex);
		moveToChar(_lineIndex - 1, previousLine.length());
	} else if(_charIndex > 0) {
		// Remove character
		line.erase(_charIndex-1, 1);
		_currentFile->editLine(_lineIndex, line);
		moveLeft();
	}
}

void Editor::eraseForward(){
	std::string line = _currentFile->getLine(_lineIndex);

	if(_charIndex == line.length() && _lineIndex < _currentFile->lineCount()-1){
		// Remove line feed
		std::string nextLine = _currentFile->getLine(_lineIndex+1);
		_currentFile->editLine(_lineIndex, line + nextLine);
		_currentFile->removeLine(_lineIndex+1);
	} else {
		// Remove character
		line.erase(_charIndex, 1);
		_currentFile->editLine(_lineIndex, line);
	}
	moveToChar(_lineIndex, _charIndex);
}

void Editor::renderRow(int row){
	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	wmove(_mainWindow, row, 0);
	wclrtoeol(_mainWindow);
	if(lineIndex < _currentFile->lineCount()){
		waddstr(_mainWindow, _currentFile->getLine(lineIndex).c_str());
	} else {
		waddch(_mainWindow, EMPTY_LINE);
	}
}

int Editor::getLineIndex(){
	return _lineIndex;
}

int Editor::getCharIndex(){
	return _charIndex;
}

void Editor::setFile(TextFile* file){
	_currentFile = file;
}
