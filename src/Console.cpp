#include "Console.hpp"

Console::Console(WINDOW* consoleWindow) : _consoleWindow { consoleWindow } {}

void Console::show(const std::string& message){
	wmove(_consoleWindow, 0, 0);
	waddstr(_consoleWindow, message.c_str());
	wclrtoeol(_consoleWindow);
	wrefresh(_consoleWindow);
}