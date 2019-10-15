#pragma once
#include "Texture.h"
#include "Vector2D.h"

class Game;

class Balloon
{
protected:
	Point2D pos_;
	double w_;
	double h_;
	Vector2D dir_;
	bool estado = true; //true = normal, false = pinchado
	Texture* texture_;
	Game* game_;

public:
	Balloon(Point2D pos, double w, double h, Vector2D dir, Texture* texture, Game* game);

	void render();
	bool update();
};

