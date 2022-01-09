#pragma once

#include <ncurses.h>
#include <string>

class Console {
	public:
		Console(WINDOW* consoleWindow);
		void show(const std::string& message);

	private:
		WINDOW* _consoleWindow;
};