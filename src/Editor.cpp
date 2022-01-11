#include "Editor.hpp"
#include "Math.hpp"

#define TABSTOP 8
#define EMPTY_LINE '~'


Editor::Editor(WINDOW* mainWindow):
_mainWindow { mainWindow },
_verticalScroll { getmaxy(mainWindow) },
_horizontalScroll { getmaxx(mainWindow) } {}

void Editor::refresh(){
		wrefresh(_mainWindow);
}

void Editor::renderFile() {
	int tempX = getcurx(_mainWindow);
	int tempY = getcury(_mainWindow);

	int maxY = getmaxy(_mainWindow);
	int i;
	for(i = _verticalScroll.getStart(); i < _verticalScroll.getEnd(); i++) {
		renderRow(i - _verticalScroll.getStart());
	}
	for(; i < maxY; i++){
		wmove(_mainWindow, i, 0);
		waddch(_mainWindow, EMPTY_LINE);
		wclrtoeol(_mainWindow);
	}

	moveTo(tempY, tempX);
}

void Editor::moveUp(){
	int row = getcury(_mainWindow) - 1;
	int col = getcurx(_mainWindow);
	moveTo(row, col);
}

void Editor::moveDown(){
	int row = getcury(_mainWindow) + 1;
	int col = getcurx(_mainWindow);
	moveTo(row, col);
}

void Editor::moveLeft(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = getLineIndex();

	if( col > 0 ) {
		std::string line = _currentFile->getLine(lineIndex);
		col = trueLength(line, charIndex(line, col)-1);
	} else if( lineIndex > 0 ){
		std::string line = _currentFile->getLine(lineIndex - 1);
		row--;
		col = trueLength(line);
	}
	moveTo(row, col);
}

void Editor::moveRight(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = getLineIndex();

	std::string line = _currentFile->getLine(lineIndex);
	if( col < trueLength(line) ) {
		col = trueLength(line, charIndex(line, col) + 1);
	} else if( lineIndex < _currentFile->lineCount()-1 ) {
		row++;
		col = 0;
	}
	moveTo(row, col);
}

void Editor::moveToStartOfFile(){
	_verticalScroll.move(-_verticalScroll.getStart());
	moveTo(0, 0);
}

void Editor::moveToEndOfFile(){
	_verticalScroll.move(_currentFile->lineCount());
	moveTo(getmaxy(_mainWindow), getmaxx(_mainWindow));
}

void Editor::moveToStartOfLine(){
	int row = getcury(_mainWindow);
	moveTo(row, 0);
}

void Editor::moveToEndOfLine(){
	int row = getcury(_mainWindow);
	int lineIndex = getLineIndex();
	std::string line = _currentFile->getLine(lineIndex);
	moveTo(row, trueLength(line));
}

void Editor::moveTo(int row, int col){
	int maxRow = getmaxy(_mainWindow);
	int overflow = row - maxRow + 1;
	int underflow = 0 - row;

	_verticalScroll.setContentSize(_currentFile->lineCount());
	if(overflow > 0){
		_verticalScroll.move(overflow);
		row = maxRow;
	} else if(underflow > 0) {
		_verticalScroll.move(-underflow);
		row = 0;
	}

	if(row > _currentFile->lineCount() - 1){
		row = _currentFile->lineCount() - 1;
	}

	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	std::string str = _currentFile->getLine(lineIndex);
	col = clamp(col, 0, trueLength(str, charIndex(str, col)));
	wmove(_mainWindow, row, col);
}

void Editor::insertChar(char c){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = getLineIndex();
	int charIndex = getCharIndex();

	std::string str = _currentFile->getLine(lineIndex);
	str.insert(charIndex, 1, c);
	_currentFile->editLine(lineIndex, str);

	moveRight();
}

void Editor::insertNewLine(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = getLineIndex();
	int charIndex = getCharIndex();

	std::string str = _currentFile->getLine(lineIndex);

	std::string firstHalf = str.substr(0, charIndex);
	std::string secondHalf = str.substr(charIndex);
	_currentFile->insertLine(lineIndex);
	_currentFile->editLine(lineIndex, firstHalf);
	_currentFile->editLine(lineIndex+1, secondHalf);
	//moveTo(row+1, 0);
	moveRight();
}

void Editor::eraseBackward(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = getLineIndex();
	int charIndex = getCharIndex();

	std::string str = _currentFile->getLine(lineIndex);

	if(charIndex == 0 && lineIndex > 0){
		// Remove line feed
		std::string firstHalf = _currentFile->getLine(lineIndex - 1);
		_currentFile->editLine(lineIndex - 1, firstHalf + str);
		_currentFile->removeLine(lineIndex);

		if(_verticalScroll.getStart() == 0){
			_verticalScroll.setContentSize(_currentFile->lineCount());
			//moveTo(row-1, firstHalf.size());
		} else {
			_verticalScroll.setContentSize(_currentFile->lineCount());
			//moveTo(row, firstHalf.size());
		}
	} else if(charIndex > 0) {
		// Remove character
		std::string firstHalf = str.substr(0, charIndex-1);
		std::string secondHalf = str.substr(charIndex);
		_currentFile->editLine(lineIndex, firstHalf + secondHalf);
		//moveTo(row, col-1);
	}
	moveLeft();
}

void Editor::eraseForward(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = getLineIndex();
	int charIndex = getCharIndex();

	std::string str = _currentFile->getLine(lineIndex);

	if(charIndex == str.length() && lineIndex < _currentFile->lineCount()-1){
		// Remove line feed
		std::string secondHalf = _currentFile->getLine(lineIndex+1);
		_currentFile->editLine(lineIndex, str + secondHalf);
		_currentFile->removeLine(lineIndex+1);
		_verticalScroll.setContentSize(_currentFile->lineCount());
		moveTo(row, col);
	} else {
		// Remove character
		str.erase(charIndex, 1);
		_currentFile->editLine(lineIndex, str);
		moveTo(row, col);
	}
}

void Editor::indent(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = getLineIndex();
	int charIndex = getCharIndex();

	std::string str = _currentFile->getLine(lineIndex);
	int tabCount = TABSTOP - (charIndex%TABSTOP);
	//std::string tab = std::string(tabCount, ' ');
	str.insert(charIndex, 1, '\t');
	_currentFile->editLine(lineIndex, str);

	//moveTo(row, col + 1);
	moveRight();
}

void Editor::renderRow(int row){
	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	wmove(_mainWindow, row, 0);
	wclrtoeol(_mainWindow);
	waddstr(_mainWindow, _currentFile->getLine(lineIndex).c_str());
}

int Editor::getLineIndex(){
	return _verticalScroll.getAbsoluteIndex(getcury(_mainWindow));
}

int Editor::getCharIndex(){
	// TODO: handle horizontal scrolling
	int lineIndex = getLineIndex();
	int cursor = getcurx(_mainWindow);
	std::string line = _currentFile->getLine(lineIndex);
	return charIndex(line, cursor);
}

void Editor::setFile(TextFile* file){
	_currentFile = file;
}

int Editor::charIndex(std::string line, int col) {
	int i;
	int length = 0;
	for(i = 0; i < line.length() && length < col; i++) {
		if(line[i] == '\t') {
			length += TABSTOP - (length % TABSTOP);
		} else {
			length++;
		}
	}
	return i;
}

int Editor::trueLength(std::string line) {
	return trueLength(line, line.length());
}

int Editor::trueLength(std::string line, int charCount) {
	int length = 0;
	for(int i = 0; i < line.length() && i < charCount; i++) {
		if(line[i] == '\t') {
			length += TABSTOP - (length % TABSTOP);
		} else {
			length++;
		}
	}
	return length;
}
