#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"
#include "checkML.h"
#include <vector>

class Game;

class Bow
{
private:
	Point2D pos_;
	double w_;
	double h_;
	Vector2D dir_;
	Arrow* loadedArrow_;
	Texture* texture_;
	Texture* textureL_;
	Texture* arrowText_;
	Game* game_;
	bool loaded;
	double angle = 0;

public:
	Bow(Point2D pos, double w, double h, Vector2D dir, Arrow* arrow, Texture* texture, Texture* textureL, Texture* arrowTex, Game* game);
	~Bow() {
		texture_ = nullptr;
		textureL_ = nullptr;
		arrowText_ = nullptr;
		game_ = nullptr;
		delete loadedArrow_;
		loadedArrow_ = nullptr;
	}

	void render(SDL_Renderer* renderer);
	void update();
	void setDir(Vector2D newdir);
	bool handleEvents(SDL_Event const& evt, vector<Arrow*>& arrows);

	void load();
	void shoot(vector<Arrow*>& arrows);
};

