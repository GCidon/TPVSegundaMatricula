#pragma once

#include "GameObject.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Texture.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(Point2D pos, int w, int h, Texture* texture);
	~SDLGameObject() {}

	virtual void render();
	virtual void update() {}
	SDL_Rect getRect();

protected:
	int w_;
	int h_;
	Texture* texture_;
	Point2D pos_;

};

