#include "PwdCommand.hpp"

bool PwdCommand::tryParse(std::string command) {
	return command == "pwd";
}

void PwdCommand::doProcess(AppContext& context) {
	std::string workingDir = context.fileBrowser()->wd();
	context.console()->display(workingDir);
}
