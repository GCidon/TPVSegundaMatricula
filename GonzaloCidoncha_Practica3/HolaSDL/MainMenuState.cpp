#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* g) : GameState(g) {
	newGame = new MenuButton(Point2D(300, 150), 200, 100, g_->texturas_[PlayB], g_, play);
	stage.push_back(newGame);
	eventHandlers_.push_back(newGame);

	exitGame = new MenuButton(Point2D(300, 300), 200, 100, g_->texturas_[ExitB], g_, exit);
	stage.push_back(exitGame);
	eventHandlers_.push_back(exitGame);
}

void MainMenuState::play(Game* g) {
	g->getGSM()->pushState(new PlayState(g));
}

void MainMenuState::exit(Game* g) {
	g->exit = true;
}
