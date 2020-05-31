#pragma once

#include "SDLGameObject.h"
#include "checkML.h"
#include <fstream>
#include <list>

class GameState;

class ArrowsGameObject :
	public SDLGameObject
{

public:
	ArrowsGameObject(double posx, double posy, double dirx, double diry, int w, int h,  double speed, int angle, Texture* texture, GameState* state);
	virtual ~ArrowsGameObject() {}

	void setItList(const std::list<GameObject*>::iterator& it);
	std::list<GameObject*>::iterator it_;

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

