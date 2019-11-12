#pragma once

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows


class GameObject {
protected:
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual bool update() = 0;
};