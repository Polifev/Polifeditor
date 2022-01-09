#pragma once
#include "Editor.hpp"

class AppContext {
	public:
		AppContext();
		void dispose();

		Editor* editor();

	private:
		Editor* _editor;
		WINDOW* _mainWindow;
		WINDOW* _consoleWindow;
		TextFile* _openedFile; // TODO: replace with multiple files manager
};