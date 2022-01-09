#include "Editor.hpp"
#include "Math.hpp"

#define TABSTOP 4
#define EMPTY_LINE '~'

Editor::Editor(WINDOW* mainWindow): _mainWindow{mainWindow}, _verticalScroll{getmaxy(mainWindow)} {
	_verticalScroll = ScrollingWindow(getmaxy(mainWindow));
}

void Editor::refresh(){
	wrefresh(_mainWindow);
}

void Editor::renderRow(int row){
	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	wmove(_mainWindow, row, 0);
	wclrtoeol(_mainWindow);
	wmove(_mainWindow, row, TABSTOP * _currentFile->getIndentation(lineIndex));
	waddstr(_mainWindow, _currentFile->getLine(lineIndex).c_str());
}

void Editor::renderFilePortion() {
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

void Editor::move(int rowDelta, int colDelta){
	int row = getcury(_mainWindow) + rowDelta;
	int col = getcurx(_mainWindow) + colDelta;
	moveTo(row, col);
}

void Editor::moveTo(int row, int col){
	int maxRow = getmaxy(_mainWindow);
	int overflow = row - maxRow + 1;
	int underflow = row;
	
	_verticalScroll.setContentSize(_currentFile->lineCount());
	if(overflow > 0){
		_verticalScroll.scrollOf(overflow);
		row = maxRow;
	} else if(underflow < 0) {
		_verticalScroll.scrollOf(underflow);
		row = 0;
	}

	if(row > _currentFile->lineCount() - 1){
		row = _currentFile->lineCount() - 1;
	}

	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	std::string str = _currentFile->getLine(lineIndex);
	int indentationOffset = _currentFile->getIndentation(lineIndex)*TABSTOP;
	col = clamp(col, indentationOffset, indentationOffset + str.size());
	wmove(_mainWindow, row, col);
}

void Editor::insertChar(char c){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = _verticalScroll.getStart() + row;
	int charIndex = col - _currentFile->getIndentation(lineIndex)*TABSTOP;

	std::string str = _currentFile->getLine(lineIndex);
	str.insert(charIndex, 1, c);
	_currentFile->editLine(lineIndex, str);

	moveTo(row, col+1);
}

void Editor::insertNewLine(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	int charIndex = col - _currentFile->getIndentation(lineIndex)*TABSTOP;

	std::string str = _currentFile->getLine(lineIndex);
	int indentation = _currentFile->getIndentation(lineIndex);

	std::string firstHalf = str.substr(0, charIndex);
	std::string secondHalf = str.substr(charIndex);
	_currentFile->insertLine(lineIndex);
	_currentFile->editLine(lineIndex, firstHalf);
	_currentFile->setIndentation(lineIndex, indentation);
	_currentFile->editLine(lineIndex+1, secondHalf);
	_currentFile->setIndentation(lineIndex+1, 0);

	moveTo(row+1, 0);
}

void Editor::eraseBackward(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	int charIndex = col - _currentFile->getIndentation(lineIndex)*TABSTOP;

	std::string str = _currentFile->getLine(lineIndex);

	if(charIndex == 0){
		if(_currentFile->getIndentation(lineIndex) > 0){
			// Remove indentation
			unindent();
		} else if(lineIndex > 0){
			// Remove line feed
			std::string firstHalf = _currentFile->getLine(lineIndex - 1);
			_currentFile->editLine(lineIndex - 1, firstHalf + str);
			_currentFile->removeLine(lineIndex);

			if(_verticalScroll.getStart() == 0){
				_verticalScroll.setContentSize(_currentFile->lineCount());
				moveTo(row-1, firstHalf.size());
			} else {
				_verticalScroll.setContentSize(_currentFile->lineCount());
				moveTo(row, firstHalf.size());
			}
		}
	} else if(charIndex > 0) {
		// Remove character
		std::string firstHalf = str.substr(0, charIndex-1);
		std::string secondHalf = str.substr(charIndex);
		_currentFile->editLine(lineIndex, firstHalf + secondHalf);
		moveTo(row, col-1);
	}
}

void Editor::eraseForward(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	int charIndex = col - _currentFile->getIndentation(lineIndex)*TABSTOP;

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
	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	_currentFile->indentLine(lineIndex);
	moveTo(row, col+TABSTOP);
}

void Editor::unindent(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex = _verticalScroll.getAbsoluteIndex(row);
	_currentFile->unindentLine(lineIndex);
	moveTo(row, col-TABSTOP);
}

std::string Editor::readMultibyteChar(){
	int i = 0;
	char buffer[256];
	buffer[i++] = wgetch(_mainWindow);
	wtimeout(_mainWindow, 0);
	while((buffer[i++] = wgetch(_mainWindow)) != -1);
	buffer[i-1] = '\0';
	wtimeout(_mainWindow, -1);
	return std::string(buffer);
}

void Editor::setFile(TextFile* file){
	_currentFile = file;
}
