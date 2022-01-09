#include "Console.hpp"

Console::Console(WINDOW* consoleWindow) : _consoleWindow { consoleWindow } {}

void Console::show(const std::string& message){
	wmove(_consoleWindow, 0, 0);
	waddstr(_consoleWindow, message.c_str());
	wclrtoeol(_consoleWindow);
	wrefresh(_consoleWindow);
}

std::string Console::readLine(std::string message, std::string placeholder){
	wmove(_consoleWindow, 0, 0);
	wclrtoeol(_consoleWindow);
	waddstr(_consoleWindow, message.c_str());
	waddstr(_consoleWindow, placeholder.c_str());

	char c = wgetch(_consoleWindow);
	if(c == '\n'){
		return placeholder;
	} else {
		ungetch(c);
		char buffer[256];
		echo();
		wgetnstr(_consoleWindow, buffer, 255);
		noecho();
		return std::string(buffer);
	}
}