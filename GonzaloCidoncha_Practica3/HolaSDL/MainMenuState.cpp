#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* g) : GameState(g) {
	newGame = new MenuButton(Point2D(300, 150), 200, 100, g_->texturas_[PlayB], g_, play);
	addGameObject(newGame);
	addEventHandler(newGame);

	loadGame = new MenuButton(Point2D(300, 300), 200, 100, g_->texturas_[LoadB], g_, load);
	addGameObject(loadGame);
	addEventHandler(loadGame);

	exitGame = new MenuButton(Point2D(300, 450), 200, 100, g_->texturas_[ExitB], g_, exit);
	addGameObject(exitGame);
	addEventHandler(exitGame);
}

MainMenuState::~MainMenuState() {
	int cosa = 1;
}

void MainMenuState::play(Game* g) {
	g->getGSM()->pushState(new PlayState(g));
}

void MainMenuState::exit(Game* g) {
	g->exit = true;
}

void MainMenuState::load(Game* g) {
	g->getGSM()->pushState(new PlayState(g));
	static_cast<PlayState*>(g->getGSM()->currentState())->loadGame("test.txt");
}
