#pragma once
#include "GameState.h"
#include "MenuButton.h"
#include "checkML.h"
class PauseState :
	public GameState
{
public:
	PauseState(Game* g);

	static void resume(Game* g);
	static void menu(Game* g);
	static void save(Game* g);

private:
	MenuButton* resumeGame;
	MenuButton* menuB;
	MenuButton* saveGame;

};

