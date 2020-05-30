#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "ArrowsGameObject.h"
#include "checkML.h"
class Arrow : public ArrowsGameObject
{
private:
	double angle_;

public:
	Arrow(Point2D pos, double w, double h, double angle, Vector2D dir, Texture* texture, GameState* state) : 
		ArrowsGameObject(pos.x_, pos.y_, dir.getX(), dir.getY(), w, h, 10, 0, texture, state)
	{
		angle_ = angle;
	}

	virtual ~Arrow() {}

	virtual void update();
	SDL_Rect getHead();
};

