#pragma once
#include "GameState.h"
class PlayState :
	public GameState
{
private:
	string name;
	int puntuacion;

	Bow* bow_;
	ScoreBoard* score;

	SDL_Rect flechasRect;
	SDL_Rect puntRect;

	int arrowsLeft = 10;
	int level;

	void collisionA(Arrow* hitter, ArrowsGameObject* hitted);
	void generate();
	void nextLevel();
	void killObject(list<GameObject*>::iterator it);

	void saveGame(string file);
	void loadGame(string file);
	void savePunt(string file);

public:
	PlayState(Game* g);
	~PlayState();

	list<Butterfly*> butterflyList_;
	list<ArrowsGameObject*> eliminated_;

	list<Arrow*> arrows_;
	list<Balloon*> balloons_;
	list<Butterfly*> butterflies_;
	list<Reward*> rewards_;

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event evt);

	void shoot();


};

