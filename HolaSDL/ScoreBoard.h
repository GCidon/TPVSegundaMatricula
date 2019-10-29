#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include "checkML.h"

class ScoreBoard
{
private:
	Texture* texture_;
	int punt = 0;
	Point2D pos_;
	double w_, h_;

public:
	ScoreBoard(Texture* texture, Point2D pos, int w, int h) : pos_(pos), texture_(texture) {
		w_ = w;
		h_ = h;
	}

	void render();
	void addPunt(int newPunt) { punt += newPunt; }
	int getPunt() { return punt; }
};

