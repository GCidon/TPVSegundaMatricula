#pragma once
#include "ArrowsGameObject.h"
#include "checkML.h"

class ScoreBoard : public ArrowsGameObject
{
private:
	int punt = 0;

public:
	ScoreBoard(Texture* texture, Point2D pos, int w, int h) : ArrowsGameObject(pos, w, h, Vector2D(0,0), texture, nullptr) {
	}

	virtual void render(SDL_Renderer* renderer);
	void addPunt(int newPunt) { punt += newPunt; }
	int getPunt() { return punt; }
};

