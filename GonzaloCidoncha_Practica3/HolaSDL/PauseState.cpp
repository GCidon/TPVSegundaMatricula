#include "PauseState.h"
#include "PlayState.h"

PauseState::PauseState(Game* g) : GameState(g) {
	resumeGame = new MenuButton(Point2D(300, 150), 200, 100, g_->texturas_[ResumeB], g_, resume);
	addGameObject(resumeGame);
	addEventHandler(resumeGame);

	saveGame = new MenuButton(Point2D(300, 300), 200, 100, g_->texturas_[SaveB], g_, save);
	addGameObject(saveGame);
	addEventHandler(saveGame);

	menuB = new MenuButton(Point2D(300, 450), 200, 100, g_->texturas_[MenuB], g_, menu);
	addGameObject(menuB);
	addEventHandler(menuB);
}

void PauseState::resume(Game* g) {
	g->getGSM()->popState();
}

void PauseState::menu(Game* g) {
	g->getGSM()->popState();
	g->getGSM()->popState();
}

void PauseState::save(Game* g) {
	g->getGSM()->popState();
	static_cast<PlayState*>(g->getGSM()->currentState())->saveGame("test.txt");
}