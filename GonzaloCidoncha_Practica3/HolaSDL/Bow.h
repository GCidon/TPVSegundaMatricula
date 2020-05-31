#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"
#include "ArrowsGameObject.h"
#include "EventHandler.h"
#include <vector>
#include "checkML.h"

class Game;

class Bow : public ArrowsGameObject, public EventHandler
{
private:
	Arrow* loadedArrow_;
	Texture* textureL_;
	Texture* arrowText_;
	bool loaded;

public:
	Bow(Point2D pos, double w, double h, Vector2D dir, Arrow* arrow, Texture* texture, Texture* textureL, Texture* arrowTex, GameState* state);

	~Bow() {
		texture_ = nullptr;
		textureL_ = nullptr;
		arrowText_ = nullptr;
		delete loadedArrow_;
		loadedArrow_ = nullptr;
	}

	virtual void render();
	virtual void update();
	void setDir(Vector2D newdir);
	virtual bool handleEvent(SDL_Event const& evt);

	void load();
	bool shoot();
	bool isLoaded();

	double getAngle() { return angulo_; }
};

