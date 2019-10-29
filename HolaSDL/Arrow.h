#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
class Arrow
{
private:
	Point2D pos_;
	Vector2D dir_;
	Texture* texture_;
	double w_;
	double h_;

public:
	Arrow(Point2D pos, double w, double h, Vector2D dir, Texture* texture) : pos_(pos), dir_(dir), texture_(texture) {
		w_ = w;
		h_ = h;
	}

	void render();
	SDL_Rect getRect();
	SDL_Rect getHead();
	void setDir(Vector2D newdir);
	void setPos(Point2D newpos);
	bool update();
};

