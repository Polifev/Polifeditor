#pragma once

#include "TextFile.hpp"
#include "ScrollingWindow.hpp"

#include <string>

#include <ncurses.h>

class Editor {
	public:
		Editor(WINDOW* mainWindow);

		void refresh();
		void renderFile();

		void moveUp();
		void moveDown();
		void moveRight();
		void moveLeft();
		void moveToStartOfFile();
		void moveToEndOfFile();
		void moveToStartOfLine();
		void moveToEndOfLine();
		void moveToLine(int lineIndex);
		void moveToChar(int lineIndex, int charIndex);

		void insertChar(char c);
		void insertNewLine();
		void eraseBackward();
		void eraseForward();

		int getCharIndex();
		int getLineIndex();

		void setFile(TextFile* file);
		
	private:
		void renderRow(int index);

		WINDOW* _mainWindow = 0;
		TextFile* _currentFile = nullptr;

		int _lineIndex = 0;
		int _charIndex = 0;

		ScrollingWindow _verticalScroll;
		//ScrollingWindow _horizontalScroll;
};
