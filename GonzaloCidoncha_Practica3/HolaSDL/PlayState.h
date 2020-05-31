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


public:
	PlayState(Game* g);
	virtual ~PlayState();

	std::list<Arrow*> arrows_;
	std::list<Balloon*> balloons_;
	std::list<Butterfly*> butterflies_;
	std::list<Reward*> rewards_;
	std::list<std::list<GameObject*>::iterator> eliminados_;

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event evt);

	void extraArrow();
	void nextLevel();
	void shoot(Arrow* arrow);

	bool collisionBalloon(Balloon* b);
	bool collisionButterfly(Butterfly* b);
	bool collisionReward(Reward* r);
	void killBalloon(std::list<GameObject*>::iterator it);
	void killButterfly(std::list<GameObject*>::iterator it);
	void killReward(std::list<GameObject*>::iterator it, list<EventHandler*>::iterator evtit);
	void killArrow(std::list<GameObject*>::iterator it);

	void saveGame(string file);
	void loadGame(string file);
	void savePunt(string file);
};

