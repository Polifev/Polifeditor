#include "SaveState.hpp"

AppState SaveState::processInput(AppContext& context){
	std::string filename = context.console()->readLine("File to write :", "");
	context.saveFile();
	context.console()->show("File written: " + filename);
	return APPSTATE_EDIT;
}
