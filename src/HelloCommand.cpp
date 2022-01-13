#include "HelloCommand.hpp"

bool HelloCommand::tryParse(std::string command) {
	return command == "hello";
}

void HelloCommand::doProcess(AppContext& context) {
	context.console()->display("Hello World !");
}
