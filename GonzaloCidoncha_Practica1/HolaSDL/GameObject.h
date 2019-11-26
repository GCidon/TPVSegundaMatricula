#pragma once
#include "SDL.h"
#include "SDL_image.h" 

class GameObject
{

public:
	virtual void render() = 0;
	virtual bool update() = 0;
};

