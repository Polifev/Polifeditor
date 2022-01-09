#include "IState.hpp"

class SaveState : public IState {
	public:
		AppState processInput(AppContext& context);
};