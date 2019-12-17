#pragma once
#include "ArrowsGameObject.h"
#include "checkML.h"
class Butterfly :
	public ArrowsGameObject
{
private:
	int row, col;
	int frame = 0;

public:
	Butterfly(double x, double y, double w, double h, Vector2D dir, Texture* texture, Game* game) : ArrowsGameObject(x, y, w, h, dir, texture, game) {
		row = col = 1;
	}

	~Butterfly();

	virtual void update();
	virtual void render();
};

