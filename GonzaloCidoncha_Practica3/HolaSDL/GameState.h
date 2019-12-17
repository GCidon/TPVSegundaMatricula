#pragma once

#include "Game.h"
#include <list>

using namespace std;

class GameState
{
protected:
	list<GameObject*> stage;
	list<EventHandler*> eventHandlers_;
	Game* g_;

public:
	GameState(Game* g);
	~GameState();

	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event evt);
};

