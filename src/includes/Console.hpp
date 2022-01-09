#pragma once

#include <ncurses.h>
#include <string>

class Console {
	public:
		Console(WINDOW* consoleWindow);
		void show(const std::string& message);
		std::string readLine(std::string message, std::string placeholder);

	private:
		WINDOW* _consoleWindow;
};