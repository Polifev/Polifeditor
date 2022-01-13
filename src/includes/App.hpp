#pragma once
#include "EditTextState.hpp"
#include "SaveState.hpp"
#include "CommandState.hpp"

class App {
	public:
		App(int argc, char** argv);
		int run();
	private:
		AppContext _context;
		IState* _currentState;
		
		EditTextState _editState;
		SaveState _saveState;
		CommandState _commandState;

		void transitionTo(AppState state);
};
