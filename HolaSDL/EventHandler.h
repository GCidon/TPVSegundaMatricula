#pragma once

#include "SDL.h"

class EventHandler
{
public:
	virtual bool handleEvent(SDL_Event const& evt) = 0;
};

