#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"

class Game;

class Bow
{
protected:
	Point2D pos_;
	double w_;
	double h_;
	Vector2D dir_;
	Arrow* loadedArrow_;
	Texture* texture_;
	Game* game_;
	bool loaded;

public:
	Bow(Point2D pos, double w, double h, Vector2D dir, Arrow* arrow, Texture* texture, Game* game);

	void render();
	void update();
	void setDir(Vector2D newdir);
	void handleEvents(SDL_Event const& evt);

	void load();
	void shoot();
};

