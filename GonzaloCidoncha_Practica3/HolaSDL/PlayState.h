#pragma once
#include "GameState.h"
#include "Arrow.h"
#include "Bow.h"
#include "Balloon.h"
#include "Butterfly.h"
#include "Reward.h"
#include "ScoreBoard.h"
#include "checkML.h"

class Game;

class PlayState :
	public GameState
{
private:

	Bow* bow_;
	ScoreBoard* score_;

	SDL_Rect flechasRect;
	SDL_Rect puntRect;

	int arrowsLeft = 10;
	int level_;

	void generate();

	void reward(Point2D pos);

	void eliminar();

	void saveGame(string file);
	void loadGame(string file);
	void savePunt(string file);

public:
	PlayState(Game* g);
	virtual ~PlayState();

	list<Arrow*> arrows_;
	list<Balloon*> balloons_;
	list<Butterfly*> butterflies_;
	list<Reward*> rewards_;
	list<list<GameObject*>::iterator> eliminados_;

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& evt);

	void extraArrow();
	void nextLevel();
	void shoot(Arrow* arrow);

	bool collisionBalloon(Balloon* b);
	bool collisionButterfly(Butterfly* b);
	bool collisionReward(Reward* r);
	void killBalloon(list<GameObject*>::iterator it);
	void killButterfly(list<GameObject*>::iterator it);
	void killReward(list<GameObject*>::iterator it);
	void killArrow(list<GameObject*>::iterator it);

};

