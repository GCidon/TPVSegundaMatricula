#pragma once
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "checkML.h"
class Reward :
	public ArrowsGameObject, public EventHandler
{
protected:

	Texture* bubbleText;

	bool inBubble = true;
	int type;

	virtual void update();
	virtual void render();
	virtual bool handleEvent(SDL_Event const& evt);

public:
	Reward(double x, double y, Texture* texture, Texture* bubble, Game* game);
};

