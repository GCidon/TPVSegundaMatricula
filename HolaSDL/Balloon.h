#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include "Arrow.h"
#include "checkML.h"
#include <vector>

class Game;

class Balloon
{
private:
	Point2D pos_;
	double w_;
	double h_;
	Vector2D dir_;
	bool estado = true; //true = normal, false = pinchado
	Texture* texture_;
	Game* game_;
	int color;
	int deadCount = 0;
	bool hit = false;

public:
	Balloon(Point2D pos, double w, double h, Vector2D dir, Texture* texture, Game* game);
	~Balloon();

	SDL_Rect getRect();
	void render();
	bool update(vector<Arrow*> arrows);
	bool isHit() { return hit; }
};

