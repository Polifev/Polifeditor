#include "Editor.hpp"
#include "Math.hpp"

#define TABSTOP 4

Editor::Editor(WINDOW* mainWindow): _mainWindow{mainWindow} {}

void Editor::refresh(){
	wrefresh(_mainWindow);
}

void Editor::renderLine(int index){
	wmove(_mainWindow, index, 0);
	wclrtoeol(_mainWindow);
	wmove(_mainWindow, index, TABSTOP * _currentFile->getIndentation(index));
	waddstr(_mainWindow, _currentFile->getLine(index).c_str());
}

void Editor::renderFilePortion(int start) {
	int maxY = getmaxy(_mainWindow);
	int i;
	for(i = 0; i < _currentFile->lineCount() && i < maxY; i++) {
		renderLine(i);
	}
	for(; i < maxY - 1; i++){
		wmove(_mainWindow, i, 0);
		waddch(_mainWindow, '~');
		wclrtoeol(_mainWindow);
	}
}

void Editor::move(int rowDelta, int colDelta){
	int row = getcury(_mainWindow) + rowDelta;
	int col = getcurx(_mainWindow) + colDelta;
	moveTo(row, col);
}

void Editor::moveTo(int row, int col){
	row = clamp(row, 0, _currentFile->lineCount()-1);
	std::string str = _currentFile->getLine(row);
	int indentationOffset = _currentFile->getIndentation(row)*TABSTOP;
	col = clamp(col, indentationOffset, indentationOffset + str.size());
	wmove(_mainWindow, row, col);
}

void Editor::insertChar(char c){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int lineIndex; // TODO will be used for v-scrolling
	int charIndex = col - _currentFile->getIndentation(row)*TABSTOP;

	std::string str = _currentFile->getLine(row);
	str.insert(charIndex, 1, c);
	_currentFile->editLine(row, str);

	// Render and replace cursor
	renderLine(row);
	moveTo(row, col+1);
}

void Editor::insertNewLine(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int charIndex = col - _currentFile->getIndentation(row)*TABSTOP;

	std::string str = _currentFile->getLine(row);
	int indentation = _currentFile->getIndentation(row);

	std::string firstHalf = str.substr(0, charIndex);
	std::string secondHalf = str.substr(charIndex);
	_currentFile->insertLine(row);
	_currentFile->editLine(row, firstHalf);
	_currentFile->setIndentation(row, indentation);
	_currentFile->editLine(row+1, secondHalf);
	_currentFile->setIndentation(row+1, 0);

	// Render and replace cursor
	renderFilePortion(0);
	moveTo(row+1, 0);
}

void Editor::eraseBackward(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int charIndex = col - _currentFile->getIndentation(row)*TABSTOP;

	std::string str = _currentFile->getLine(row);

	if(charIndex == 0){
		if(_currentFile->getIndentation(row) > 0){
			unindent();
		} else if(row > 0){
			// Remove line feed
			std::string firstHalf = _currentFile->getLine(row - 1);
			_currentFile->editLine(row - 1, firstHalf + str);
			_currentFile->removeLine(row);
			renderFilePortion(0);
			moveTo(row-1, firstHalf.size());
		}
	} else if(charIndex > 0) {
		// Remove character
		std::string firstHalf = str.substr(0, charIndex-1);
		std::string secondHalf = str.substr(charIndex);
		_currentFile->editLine(row, firstHalf + secondHalf);
		renderLine(row);
		moveTo(row, col-1);
	}
}

void Editor::eraseForward(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);
	int charIndex = col - _currentFile->getIndentation(row)*TABSTOP;

	std::string str = _currentFile->getLine(row);

	if(charIndex == str.length() && row < _currentFile->lineCount()-1){
		// Remove line feed
		std::string secondHalf = _currentFile->getLine(row+1);
		_currentFile->editLine(row, str + secondHalf);
		_currentFile->removeLine(row+1);
		renderFilePortion(0);
		moveTo(row, col);
	} else {
		// Remove character
		str.erase(col, 1);
		_currentFile->editLine(row, str);
		renderLine(row);
		moveTo(row, col);
	}
}

void Editor::indent(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);

	_currentFile->indentLine(row);
	renderLine(row);
	moveTo(row, col+TABSTOP);
}

void Editor::unindent(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);

	_currentFile->unindentLine(row);
	renderLine(row);
	moveTo(row, col-TABSTOP);
}

char Editor::readChar(){
	// TODO handle multi-byte char
	return wgetch(_mainWindow);
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

/*void Editor::newTextFile(std::string filename){
	if(_currentFile != nullptr){
		delete _currentFile;
	}
	_currentFile = new TextFile(filename);
	//printToConsole(L"Opened \"" + filename +"\"");
}


void Editor::openTextFile(std::string filename){
	if(_currentFile != nullptr){
		delete _currentFile;
	}
	_currentFile = new TextFile(filename);
	_currentFile->read();
	//printToConsole("Opened \"" + filename +"\"");
}

void Editor::save(){
	if(_currentFile != nullptr){
		_currentFile->write();
		//printToConsole("File saved.");
	} else {
		
	}
}*/
