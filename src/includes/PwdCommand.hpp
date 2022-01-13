#pragma once
#include "AbstractCommand.hpp"

class PwdCommand : public AbstractCommand {
protected:
	bool tryParse(std::string command);
	void doProcess(AppContext& context);
};
