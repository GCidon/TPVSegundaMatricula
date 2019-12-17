#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "List.h"
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

	SDL_Rect getRect();
	SDL_Rect getDestRect();
	SDL_Rect getCollisionRect();

public:
	ArrowsGameObject(double x, double y, double w, double h, Vector2D dir, Texture* texture, Game* game);

	void setItList(list<GameObject*>::iterator it);
	list<GameObject*>::iterator it_;
	bool hit = false;
	Point2D getPos() { return pos_; }
	double getW() { return w_; }
	double getH() { return h_; }
	virtual void render();
	virtual void update();
	void loadFromFile();
	void saveToFile();
};

