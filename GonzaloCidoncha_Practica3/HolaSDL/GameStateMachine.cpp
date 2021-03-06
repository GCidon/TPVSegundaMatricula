#include "GameStateMachine.h"
#include "GameState.h"

GameStateMachine::~GameStateMachine() {
	while (!gameStates_.empty())
	{
		popState();
	}
}

GameState* GameStateMachine::currentState() {
	return gameStates_.top();
}

void GameStateMachine::pushState(GameState* gs) {
	gameStates_.push(gs);
}

void GameStateMachine::popState() {
	if (!gameStates_.empty()) {
		delete gameStates_.top();
		gameStates_.top() = nullptr;
		gameStates_.pop();
	}
}

void GameStateMachine::changeState(GameState* gs) {
	popState();
	pushState(gs);
}
