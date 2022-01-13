#pragma once
#include "Editor.hpp"
#include "Console.hpp"
#include "Keyboard.hpp"
#include "FileBrowser.hpp"

class AppContext {
	public:
		AppContext();
		void dispose();

		Editor* editor();
		Console* console();
		Keyboard* keyboard();
		FileBrowser* fileBrowser();
		TextFile* openedFile();

		std::string command();
		void command(std::string command);

		void saveFile();
	private:
		WINDOW* _mainWindow;
		WINDOW* _consoleWindow;

		Keyboard* _keyboard;
		Editor* _editor;
		Console* _console;
		FileBrowser* _fileBrowser;
		TextFile* _openedFile; // TODO: replace with multiple files manager
		std::string _command;
};