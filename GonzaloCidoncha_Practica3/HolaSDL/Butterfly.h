#pragma once
#include "ArrowsGameObject.h"
#include "checkML.h"
class GameState;
class Butterfly :
	public ArrowsGameObject
{
private:
	int row, col;
	int frame = 0;

public:
	Butterfly(double x, double y, double w, double h, Vector2D dir, Texture* texture, GameState* state) : ArrowsGameObject(x, y, dir.getX(), dir.getY(), w, h, 0, 0, texture, state) {
		row = col = 1;
		speed_ = 1;
	}

	~Butterfly();

	virtual void update();
	virtual void render();

	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);
};

