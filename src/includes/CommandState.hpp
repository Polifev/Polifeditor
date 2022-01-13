#pragma once
#include "IState.hpp"
#include "CommandLibrary.hpp"
#include <string>

class CommandState : public IState {
public:
	CommandState();
	AppState processInput(AppContext& context);
private:
	std::string _command;
	CommandLibrary _library;
};
