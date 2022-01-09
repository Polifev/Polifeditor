#pragma once
#include "IState.hpp"

class App {
	public:
		App(int argc, char** argv);
		int run();
	private:
		AppContext _context;
		IState* _currentState;
		
		void transitionTo(AppState state);
};