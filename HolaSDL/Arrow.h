#pragma once
#include "Vector2D.h"
#include "Texture.h"
class Arrow
{
protected:
	Point2D pos_;
	Vector2D dir_;
	Texture* texture_;

public:
	Arrow(Point2D pos, Vector2D dir, Texture* texture) : pos_(pos), dir_(dir), texture_(texture) {}

	void render();
	SDL_Rect getRect();
	void setDir(Vector2D newdir);
	bool update();
};

