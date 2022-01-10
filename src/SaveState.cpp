#include "SaveState.hpp"

AppState SaveState::processInput(AppContext& context){
	
	/*std::string filename = "/home/pol/texte.txt";
	context.console()->display("File to write (\'Esc\' to cancel): " + filename);*/

	//context.fileBrowser()->cd("/");
	//std::vector<std::string> files = context.fileBrowser()->ls();
	TextFile* file = context.openedFile();

	context.console()->display("Write file (Enter: save, Esc: cancel): " + file->filename());
	std::string response = context.keyboard()->readMultibyteChar();

	char c = response[0];
	if(response.length() == 1){
		if(c == '\n'){
			context.saveFile();
			context.console()->display("File written: ");
			return APPSTATE_EDIT;
		} else if(c == 27) {
			context.console()->display("Cancelled...");
			return APPSTATE_EDIT;
		} else if(c == 127) {
			file->filename(file->filename().substr(0, file->filename().length() - 2));
			return APPSTATE_SAVE;
		} else {
			if(!iscntrl(c)){
				file->filename(file->filename() + c);
			}
			return APPSTATE_SAVE;
		}
	}
	return APPSTATE_SAVE;
}
