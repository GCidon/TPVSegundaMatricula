#pragma once
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "checkML.h"

class PlayState;

class Reward :
	public ArrowsGameObject, public EventHandler
{
protected:

	PlayState* playstate;
	int type;

	virtual void update();
	virtual void render();
	virtual bool handleEvent(SDL_Event const& evt);

public:
	Reward(double x, double y, Texture* texture, PlayState* ps, Game* game);
};

