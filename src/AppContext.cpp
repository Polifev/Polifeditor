#include "AppContext.hpp"

AppContext::AppContext(){
	initscr();
	noecho();
	_mainWindow = subwin(stdscr, LINES-1, COLS, 0, 0);
	_consoleWindow = subwin(stdscr, 1, COLS, LINES-1, 0);

	_openedFile = new TextFile("/home/pol/texte.txt");
	_openedFile->read();
	
	_editor = new Editor(_mainWindow);
	_editor->setFile(_openedFile);
	_editor->renderFilePortion();
	_editor->moveTo(0, 0);
	_editor->refresh();

	_console = new Console(_consoleWindow);
}

void AppContext::dispose(){
	delete _editor;
	delete _console;
	delete _openedFile;
	endwin();
}

Editor* AppContext::editor(){
	return _editor;
}

Console* AppContext::console(){
	return _console;
}

void AppContext::saveFile() {
	_openedFile->write();
}