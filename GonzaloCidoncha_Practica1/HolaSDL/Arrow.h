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
	Arrow(Point2D pos, double w, double h, double angle, Vector2D dir, Texture* texture) : 
		ArrowsGameObject(pos.x_, pos.y_, w, h, dir, texture, nullptr)
	{
		angle_ = angle;
	}

	virtual void render(SDL_Renderer* renderer);
	SDL_Rect getHead();
	void setDir(Vector2D newdir);
	void setPos(Point2D newpos);
	virtual bool update();
};

