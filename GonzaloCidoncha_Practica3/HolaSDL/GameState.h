#pragma once

#include "Game.h"
#include "SDLGameObject.h"
#include "checkML.h"

using namespace std;

class GameState
{
protected:
	list<GameObject*> stage_;
	list<EventHandler*> eventHandlers_;
	Game* g_;

	void addGameObject(SDLGameObject* obj);
	void addEventHandler(EventHandler* obj);

public:
	GameState(Game* g);
	virtual ~GameState();

	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event evt);
};

