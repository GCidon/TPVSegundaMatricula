#pragma once
#include "checkML.h"

#include "SDLGameObject.h"
#include <fstream>
#include <list>

class GameState;

class ArrowsGameObject :
	public SDLGameObject
{

public:
	ArrowsGameObject(double posx, double posy, double dirx, double diry, int w, int h,  double speed, int angle, Texture* texture, GameState* state);

	void setItList(list<GameObject*>::iterator it);
	list<GameObject*>::iterator it_;

	virtual void render();
	virtual void update();
	SDL_Rect getRect() const;
	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);

protected:
	Vector2D dir_;
	int angulo_;
	double speed_;

};

