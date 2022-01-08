#include "Editor.hpp"
#include "Math.hpp"

Editor::Editor() {
	initscr();
	noecho();
	_mainWindow = subwin(stdscr, LINES-1, COLS, 0, 0);
	_console = subwin(stdscr, 1, COLS, LINES-1, 0);
}

void Editor::refresh(){
	wrefresh(_mainWindow);
}

void Editor::renderLine(int index){
	wmove(_mainWindow, index, 0);
	waddstr(_mainWindow, _currentFile->getLine(index).c_str());
	wclrtoeol(_mainWindow);
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

void Editor::printToConsole(std::string message){
	wmove(_console, 0, 0);
	waddstr(_console, message.c_str());
	wclrtoeol(_console);
	wrefresh(_console);
}

void Editor::move(int rowDelta, int colDelta){
	int row = getcury(_mainWindow) + rowDelta;
	int col = getcurx(_mainWindow) + colDelta;
	moveTo(row, col);
}

void Editor::moveTo(int row, int col){
	row = clamp(row, 0, _currentFile->lineCount()-1);
	std::string str = _currentFile->getLine(row);
	col = clamp(col, 0, str.size());
	wmove(_mainWindow, row, col);
}

void Editor::insertChar(char c){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);

	std::string str = _currentFile->getLine(row);
	str.insert(col, 1, c);
	_currentFile->editLine(row, str);

	// Render and replace cursor
	renderLine(row);
	wmove(_mainWindow, row, col+1);
}

void Editor::insertNewLine(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);

	std::string str = _currentFile->getLine(row);
	std::string firstHalf = str.substr(0, col);
	std::string secondHalf = str.substr(col);
	_currentFile->insertLine(row);
	_currentFile->editLine(row, firstHalf);
	_currentFile->editLine(row+1, secondHalf);

	// Render and replace cursor
	renderFilePortion(0);
	wmove(_mainWindow, row+1, 0);
}

void Editor::eraseBackward(){
	int row = getcury(_mainWindow);
	int col = getcurx(_mainWindow);

	std::string str = _currentFile->getLine(row);

	if(col == 0 && row > 0){
		// Remove line feed
		std::string firstHalf = _currentFile->getLine(row - 1);
		_currentFile->editLine(row - 1, firstHalf + str);
		_currentFile->removeLine(row);
		renderFilePortion(0);
		wmove(_mainWindow, row-1, firstHalf.size());
	} else if(col > 0) {
		// Remove character
		std::string firstHalf = str.substr(0, col-1);
		std::string secondHalf = str.substr(col);
		_currentFile->editLine(row, firstHalf + secondHalf);
		renderLine(row);
		wmove(_mainWindow, row, col-1);
	}
}

void Editor::eraseForward(){
	//TODO
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

void Editor::newTextFile(std::string filename){
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
}

void Editor::dispose(){
	if(_currentFile != nullptr){
		delete _currentFile;
	}
	
	//free(_mainWindow);
	//free(_console);
	endwin();
}