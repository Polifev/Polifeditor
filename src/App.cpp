#include "App.hpp"
#include "EditTextState.hpp"
#include "SaveState.hpp"
#include "CommandState.hpp"

App::App(int argc, char** argv) {
	_currentState = &_editState;
	if(argc > 1){
		TextFile* file = _context.openedFile();
		file->filename(std::string(argv[1]));
		if(file->readyToRead()){
			file->read();
		}
		_context.editor()->renderFile();
		_context.editor()->refresh();
	}
}

int App::run(){
	AppState state = APPSTATE_INIT;
	transitionTo(APPSTATE_EDIT);
	while(state != APPSTATE_EXIT) {
		AppState oldState = state;
		state = _currentState->processInput(_context);

		if(state != oldState && state != APPSTATE_EXIT){
			transitionTo(state);
		}
	}
	_context.dispose();
	return 0;
}

void App::transitionTo(AppState state){
	switch (state)
	{
	case APPSTATE_EDIT:
		_currentState = &_editState;
		break;
	case APPSTATE_SAVE:
		_currentState = &_saveState;
		break;
	case APPSTATE_COMMAND:
		_currentState = &_commandState;
		break;
	default:
		break;
	}
}
