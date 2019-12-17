#pragma once
#include "GameState.h"
#include "MenuButton.h"
class EndState :
	public GameState
{
public:
	EndState(Game* g);

	static void menu(Game* g);
	static void exit(Game* g);

private:
	MenuButton* menuB;
	MenuButton* exitGame;
};

