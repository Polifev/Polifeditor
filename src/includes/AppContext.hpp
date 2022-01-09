#pragma once
#include "Editor.hpp"
#include "Console.hpp"

class AppContext {
	public:
		AppContext();
		void dispose();

		Editor* editor();
		Console* console();

	private:
		WINDOW* _mainWindow;
		WINDOW* _consoleWindow;

		Editor* _editor;
		Console* _console;
		TextFile* _openedFile; // TODO: replace with multiple files manager
};