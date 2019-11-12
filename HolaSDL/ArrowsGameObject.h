#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include <list>

class Game;

class ArrowsGameObject : public GameObject {
protected:

	Point2D pos_;
	double w_, h_;
	Vector2D dir_;
	Texture* texture_;
	Game* game_;
	list<ArrowsGameObject>::iterator it_;

public:
	ArrowsGameObject(Point2D pos, double w, double h, Vector2D dir, Texture* texture, Game* game);
	virtual ~ArrowsGameObject();

	virtual void render(SDL_Renderer* renderer);
	virtual bool update();
	virtual SDL_Rect getRect();
};
