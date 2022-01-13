#include "IState.hpp"

class CommandState : public IState {
public:
	AppState processInput(AppContext& context);
};
