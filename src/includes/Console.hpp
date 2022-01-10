#pragma once

#include <ncurses.h>
#include <string>

class Console {
	public:
		Console(WINDOW* consoleWindow);
		void display(const std::string& message);
		void append(const std::string& message);
		void clear();

	private:
		WINDOW* _consoleWindow;
		int _cursorPos = 0;
};