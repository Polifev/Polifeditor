#pragma once
#include "AbstractCommand.hpp"

class HelloCommand : public AbstractCommand {
protected:
	bool tryParse(std::string command);
	void doProcess(AppContext& context);
};
