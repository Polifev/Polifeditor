#include "SaveState.hpp"

AppState SaveState::processInput(AppContext& context){
	context.saveFile();
	context.console()->show("File written");
	return APPSTATE_EDIT;
}
