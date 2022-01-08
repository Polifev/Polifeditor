#pragma once

#include "TextFile.hpp"

#include <string>

#include <ncurses.h>

class Editor {
	public:
		Editor();
		void refresh();
		void renderLine(int index);
		void renderFilePortion(int start);
		void printToConsole(std::string message);

		void move(int rowDelta, int colDelta);
		void moveTo(int row, int col);

		void insertChar(char c);
		void insertNewLine();
		void eraseBackward();
		void eraseForward();

		char readChar();
		std::string readMultibyteChar();

		void newTextFile(std::string filename);
		void openTextFile(std::string filename);
		void save();
		void dispose();

	private:
		WINDOW* _mainWindow = 0;
		WINDOW* _console = 0;
		TextFile* _currentFile = nullptr;
};