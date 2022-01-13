#include "CommandLibrary.hpp"

bool CommandLibrary::matchAndProcess(std::string command, AppContext& context) {
	for(AbstractCommand* c : _commands) {
		if(c->tryProcess(command, context)){
			return true;
		}
	}
	return false;
}

void CommandLibrary::registerCommand(AbstractCommand* command) {
	_commands.push_back(command);
}

void CommandLibrary::dispose() {
	for(AbstractCommand* c : _commands) {
		delete c;
	}
}