#include "CommandState.hpp"
#include "HelloCommand.hpp"
#include "PwdCommand.hpp"

CommandState::CommandState() {
	_library.registerCommand(new HelloCommand());
	_library.registerCommand(new PwdCommand());
}

AppState CommandState::processInput(AppContext& context){
	context.console()->display("> " + _command);
	std::string response = context.keyboard()->readMultibyteChar();
	char c = response[0];

	if(response.length() == 1){
		if(c == '\n'){
			if(! _library.matchAndProcess(_command, context)) {
				context.console()->display("Command \"" + _command + "\" not found");
			}
			_command = "";
			return APPSTATE_EDIT;
		} else if(c == 27) {
			_command = "";
			return APPSTATE_EDIT;
		} else if(c == 127) {
			_command.pop_back();
			return APPSTATE_COMMAND;
		} else {
			if(!iscntrl(c)){
				_command.push_back(c);
			}
			return APPSTATE_COMMAND;
		}
	}
	return APPSTATE_COMMAND;
}
