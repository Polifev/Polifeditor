#pragma once
#include "AbstractCommand.hpp"
#include "AppContext.hpp"
#include <vector>

class CommandLibrary {
public:
	bool matchAndProcess(std::string command, AppContext& context);
	void registerCommand(AbstractCommand* command);
	void dispose();
private:
	std::vector<AbstractCommand*> _commands;
};
