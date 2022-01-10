#include "Console.hpp"

Console::Console(WINDOW* consoleWindow) : _consoleWindow { consoleWindow } {}

void Console::display(const std::string& message){
	clear();
	append(message);
	wrefresh(_consoleWindow);
}

void Console::append(const std::string& message){
	wmove(_consoleWindow, 0, _cursorPos);
	waddstr(_consoleWindow, message.c_str());
	_cursorPos += message.length();
	wrefresh(_consoleWindow);
}

void Console::clear(){
	wmove(_consoleWindow, 0, 0);
	wclrtoeol(_consoleWindow);
	_cursorPos = 0;
}