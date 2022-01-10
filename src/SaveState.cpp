#include "SaveState.hpp"

AppState SaveState::processInput(AppContext& context){
	std::string filename = "/home/pol/texte.txt";
	context.console()->display("File to write (\'Esc\' to cancel): " + filename);

	std::string response = context.keyboard()->readMultibyteChar();

	if(response[0] == '\n'){
		context.saveFile();
		context.console()->display("File written: " + filename);
		return APPSTATE_EDIT;
	} else if(response[0] == 27) {
		context.console()->display("Cancelled...");
		return APPSTATE_EDIT;
	} else {
		return APPSTATE_SAVE;
	}
}
