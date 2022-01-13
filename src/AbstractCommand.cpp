#include "AbstractCommand.hpp"

bool AbstractCommand::tryProcess(std::string command, AppContext& context) {
	if(tryParse(command)) {
		doProcess(context);
		return true;
	} else {
		return false;
	}
}
