#pragma once
#include "SDLGameObject.h"
#include "EventHandler.h"
#include "checkML.h"

class Game;
class PlayState;

using CallBackOnClick = void(Game* g);

class MenuButton :
	public SDLGameObject, public EventHandler
{
protected:
	CallBackOnClick* cb_;
	Game* g_;
	
public:
	MenuButton(Point2D pos, int w, int h, Texture* texture, Game* g, CallBackOnClick* callback);
	virtual ~MenuButton() {
		cb_ = nullptr;
		g_ = nullptr;
	}
	virtual bool handleEvent(SDL_Event const& evt);
};

