#pragma once
#include "ArrowsGameObject.h"
#include "Arrow.h"
#include "checkML.h"
#include <vector>

class Game;

class Bow : public ArrowsGameObject
{
private:
	Arrow* loadedArrow_;
	Texture* textureL_;
	Texture* arrowText_;
	bool loaded;
	double angle = 0;

public:
	Bow(Point2D pos, double w, double h, Vector2D dir, Arrow* arrow, Texture* texture, Texture* textureL, Texture* arrowTex, Game* game);
	~Bow() {
		textureL_ = nullptr;
		arrowText_ = nullptr;
		delete loadedArrow_;
		loadedArrow_ = nullptr;
	}

	virtual void render(SDL_Renderer* renderer);
	virtual bool update();
	void setDir(Vector2D newdir);
	bool handleEvents(SDL_Event const& evt, vector<Arrow*>& arrows);

	void load();
	void shoot(vector<Arrow*>& arrows);
};

