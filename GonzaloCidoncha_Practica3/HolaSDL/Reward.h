#pragma once
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "checkML.h"

class GameState;

class Reward :
	public ArrowsGameObject, public EventHandler
{
protected:

	int type_;

	bool burbuja_;

	Texture* burbujaText;

	virtual void update();
	virtual void render();
	virtual bool handleEvent(SDL_Event const& evt);

public:
	Reward(double x, double y, Texture* texture, Texture* burbuja, GameState* state);

	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);
};

