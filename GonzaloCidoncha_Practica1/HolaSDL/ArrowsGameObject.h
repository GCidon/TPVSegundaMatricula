#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include <list>

class Game;

class ArrowsGameObject :
	public GameObject
{
protected:
	Point2D pos_;
	double w_, h_;
	Vector2D dir_;
	Texture* texture_;
	Game* game_;
	list<ArrowsGameObject>::iterator it_;

	SDL_Rect getRect();
	SDL_Rect getDestRect();
	SDL_Rect getCollisionRect();
	void setItList();

public:
	ArrowsGameObject(double x, double y, double w, double h, Vector2D dir, Texture* texture, Game* game);

	virtual void render();
	virtual bool update();
	void loadFromFile();
	void saveToFile();
};

