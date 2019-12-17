#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include "Arrow.h"
#include "ArrowsGameObject.h"
#include "checkML.h"
#include <vector>

class Game;

class Balloon : public ArrowsGameObject
{
private:
	bool estado = true; //true = normal, false = pinchado
	int color;
	int deadCount = 0;

public:
	Balloon(Point2D pos, double w, double h, Vector2D dir, Texture* texture, Game* game);
	~Balloon();

	virtual void render();
	virtual void update();
	bool isHit() { return hit; }
};

