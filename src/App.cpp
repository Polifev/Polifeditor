#include "App.hpp"
#include "EditTextState.hpp"

App::App(int argc, char** argv) {
	_currentState = new EditTextState();
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
	delete _currentState;
	switch (state)
	{
	case APPSTATE_EDIT:
		_currentState = new EditTextState();
		break;
	default:
		break;
	}
}