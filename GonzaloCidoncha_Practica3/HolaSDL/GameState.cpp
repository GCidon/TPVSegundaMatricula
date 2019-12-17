#include "GameState.h"

GameState::GameState(Game* g) {
	g_ = g;
}

GameState::~GameState() {
	for (auto obj : stage) delete obj;
}

void GameState::update() {
	for (auto obj : stage) obj->update();
}

void GameState::render() {
	for (auto obj : stage) obj->render();
}

void GameState::handleEvents(SDL_Event evt) {
	for (auto obj : eventHandlers_) obj->handleEvent(evt);
}
