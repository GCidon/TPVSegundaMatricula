#pragma once

#include <stack>
#include "checkML.h"

class GameState;

using namespace std;

class GameStateMachine
{
private:
	stack<GameState*> gameStates_;

public:
	GameStateMachine() {}
	~GameStateMachine();

	GameState* currentState();	
	void pushState(GameState* gs);
	void changeState(GameState* gs);
	void popState();
};

