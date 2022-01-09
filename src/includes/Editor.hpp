#pragma once

#include "TextFile.hpp"
#include "ScrollingWindow.hpp"

#include <string>

#include <ncurses.h>

class Editor {
	public:
		Editor(WINDOW* mainWindow);
		void refresh();
		void renderRow(int index);
		void renderFilePortion();

		void move(int rowDelta, int colDelta);
		void moveTo(int row, int col);

		void insertChar(char c);
		void insertNewLine();
		void eraseBackward();
		void eraseForward();
		void indent();
		void unindent();

		std::string readMultibyteChar();

		void setFile(TextFile* file);

	private:
		WINDOW* _mainWindow = 0;
		TextFile* _currentFile = nullptr;

		ScrollingWindow _verticalScroll;
};