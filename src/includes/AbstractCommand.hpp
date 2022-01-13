#pragma once
#include "AppContext.hpp"
#include <string>

class AbstractCommand {
public:
	bool tryProcess(std::string command, AppContext& context);
protected:
	virtual bool tryParse(std::string command) = 0;
	virtual void doProcess(AppContext& context) = 0;
};
