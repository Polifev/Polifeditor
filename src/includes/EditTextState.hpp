#pragma once
#include "IState.hpp"

class EditTextState : public IState {
	public:
		AppState processInput(AppContext& context);
};