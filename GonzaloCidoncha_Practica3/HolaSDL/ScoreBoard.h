#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include "ArrowsGameObject.h"
#include "checkML.h"

class ScoreBoard : public ArrowsGameObject
{
private:
	int punt = 0;

public:
	ScoreBoard(Texture* texture, Point2D pos, int w, int h) : ArrowsGameObject(pos.x_, pos.y_, 0, 0, w, h, 0, 0, texture, nullptr) {}

	virtual void render();
	void addPunt(int newPunt) { punt += newPunt; }
	int getPunt() { return punt; }
};

