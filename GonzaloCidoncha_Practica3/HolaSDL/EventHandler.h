#pragma once
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "checkML.h"

class EventHandler
{
public:
	virtual bool handleEvent(SDL_Event const& evt) = 0;
};

