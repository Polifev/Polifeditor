#include "CommandState.hpp"

AppState CommandState::processInput(AppContext& context) {
	context.console()->display("Welcome in command state !");
	return APPSTATE_EDIT;
}
