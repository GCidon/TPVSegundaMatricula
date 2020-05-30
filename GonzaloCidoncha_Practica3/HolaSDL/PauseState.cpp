#include "PauseState.h"

PauseState::PauseState(Game* g) : GameState(g) {
	resumeGame = new MenuButton(Point2D(300, 150), 200, 100, g_->texturas_[ResumeB], g_, resume);
	stage_.push_back(resumeGame);
	eventHandlers_.push_back(resumeGame);

	menuB = new MenuButton(Point2D(300, 300), 200, 100, g_->texturas_[MenuB], g_, menu);
	stage_.push_back(menuB); 
	eventHandlers_.push_back(menuB);
}

void PauseState::resume(Game* g) {
	g->getGSM()->popState();
}

void PauseState::menu(Game* g) {
	g->getGSM()->popState();
	g->getGSM()->popState();
}