#pragma once
#include "ArrowsGameObject.h"
#include "checkML.h"

class PlayState;

class Balloon : public ArrowsGameObject
{
private:
	bool estado = true; //true = normal, false = pinchado
	int color;
	int deadCount = 0;

public:
	Balloon(Point2D pos, Vector2D dir, int w, int h, double speed, Texture* texture, GameState* state);
	virtual ~Balloon();

	virtual void render();
	virtual void update();
	bool isHit() { return estado; }

	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);
};

