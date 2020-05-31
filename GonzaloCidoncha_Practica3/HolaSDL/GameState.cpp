#include "GameState.h"

GameState::GameState(Game* g) {
	g_ = g;
}

GameState::~GameState() {
	for (GameObject* obj : stage_)
	{
		delete obj;
		obj = nullptr;
	}
	stage_.clear();
	eventHandlers_.clear();
}

void GameState::update() {
	for (auto obj : stage_) obj->update();
}

void GameState::render() {
	for (auto obj : stage_) obj->render();
}

void GameState::handleEvents(SDL_Event evt) {
	for (auto obj : eventHandlers_) 
		obj->handleEvent(evt);
}

void GameState::addGameObject(SDLGameObject* obj)
{
	std::list<GameObject*>::iterator it = stage_.insert(stage_.end(), obj);

	if (dynamic_cast<ArrowsGameObject*>(obj))
		static_cast<ArrowsGameObject*>(obj)->setItList(it);
}

void GameState::addEventHandler(EventHandler* obj)
{
	std::list<EventHandler*>::iterator it = eventHandlers_.insert(eventHandlers_.end(), obj);
	obj->setItHandler(it);
}