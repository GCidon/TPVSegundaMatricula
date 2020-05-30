#include "EndState.h"
#include "MainMenuState.h"

EndState::EndState(Game* g) : GameState(g) {
	menuB = new MenuButton(Point2D(10, 500), 150, 75, g_->texturas_[MenuB], g_, menu);
	stage_.push_back(menuB);
	eventHandlers_.push_back(menuB);

	exitGame = new MenuButton(Point2D(600, 500), 150, 75, g_->texturas_[ExitB], g_, exit);
	stage_.push_back(exitGame);
	eventHandlers_.push_back(exitGame);
}

void EndState::menu(Game* g) {
	g->getGSM()->pushState(new MainMenuState(g));
}

void EndState::exit(Game* g) {
	g->exit = true;
}
