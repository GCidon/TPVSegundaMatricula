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
	~ScoreBoard() {}

	virtual void render();
	void addPunt(int newPunt) { 
		if (punt >= 0)
			punt += newPunt;
		else punt = 0;
	}
	int getPunt() { return punt; }
	void setPunt(int puntu) { punt = puntu; }
};

