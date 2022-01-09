#pragma once
#include "AppState.hpp"
#include "AppContext.hpp"

class IState {
	public:
		virtual AppState processInput(AppContext& context) = 0;
};