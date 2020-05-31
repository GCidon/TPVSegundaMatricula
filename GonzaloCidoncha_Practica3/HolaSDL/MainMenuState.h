#pragma once
#include "GameState.h"
#include "MenuButton.h"

#include "checkML.h"
class MainMenuState :
	public GameState
{

public:
	MainMenuState(Game* g);
	virtual ~MainMenuState();

	static void play(Game* g);
	static void load(Game* g);
	static void exit(Game* g);

private:
	MenuButton* newGame;
	MenuButton* exitGame;
	MenuButton* loadGame;
};

