#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include "checkML.h"
#include <vector>

class Game;

class Bow : public ArrowsGameObject, public EventHandler
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
		texture_ = nullptr;
		textureL_ = nullptr;
		arrowText_ = nullptr;
		game_ = nullptr;
		delete loadedArrow_;
		loadedArrow_ = nullptr;
	}

	virtual void render(SDL_Renderer* renderer);
	virtual bool update();
	void setDir(Vector2D newdir);
	bool handleEvents(SDL_Event const& evt, vector<Arrow*>& arrows);
	virtual bool handleEvent(SDL_Event const& evt) { return false; }

	void load();
	void shoot(vector<Arrow*>& arrows);
};

