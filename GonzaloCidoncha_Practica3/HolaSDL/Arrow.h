#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "ArrowsGameObject.h"
#include "checkML.h"

class Arrow : public ArrowsGameObject
{

public:
	Arrow(Point2D pos, double w, double h, double angle, Vector2D dir, Texture* texture, GameState* state) : 
		ArrowsGameObject(pos.x_, pos.y_, dir.getX(), dir.getY(), w, h, 10, 0, texture, state)
	{
		angulo_ = angle;
		dir_.setX(std::cos((angulo_ * 3.14) / 180)); 
		dir_.setY(std::sin((angulo_ * 3.14) / 180));
	}

	virtual ~Arrow() {}

	virtual void update();
	SDL_Rect getHead();
};

