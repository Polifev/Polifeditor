#pragma once

#include "TextFile.hpp"

#include <string>

#include <ncurses.h>

class Editor {
	public:
		Editor(WINDOW* mainWindow);
		void refresh();
		void renderLine(int index);
		void renderFilePortion(int start);
		//void printToConsole(std::string message);

		void move(int rowDelta, int colDelta);
		void moveTo(int row, int col);

		void insertChar(char c);
		void insertNewLine();
		void eraseBackward();
		void eraseForward();

		char readChar();
		std::string readMultibyteChar();

		void setFile(TextFile* file);

		//void newTextFile(std::string filename);
		//void openTextFile(std::string filename);
		//void save();

	private:
		WINDOW* _mainWindow = 0;
		TextFile* _currentFile = nullptr;
		//WINDOW* _console = 0;
};