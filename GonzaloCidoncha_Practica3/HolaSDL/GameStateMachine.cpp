#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine() {
	while (!gameStates_.empty())
	{
		delete gameStates_.top();
		gameStates_.pop();
	}
}

GameState* GameStateMachine::currentState() {
	return gameStates_.top();
}

void GameStateMachine::pushState(GameState* gs) {
	gameStates_.push(gs);
}

void GameStateMachine::popState() {
	delete gameStates_.top();
	gameStates_.pop();
}

void GameStateMachine::changeState(GameState* gs) {
	popState();
	pushState(gs);
}
