#pragma once
#include "Editor.hpp"
#include "Console.hpp"
#include "Keyboard.hpp"

class AppContext {
	public:
		AppContext();
		void dispose();

		Editor* editor();
		Console* console();
		Keyboard* keyboard();

		void saveFile();
	private:
		WINDOW* _mainWindow;
		WINDOW* _consoleWindow;

		Keyboard* _keyboard;
		Editor* _editor;
		Console* _console;
		TextFile* _openedFile; // TODO: replace with multiple files manager
};