#include "Butterfly.h"
#include "GameState.h"
#include "PlayState.h"

void Butterfly::render() {
	int timeperframe = 300 / texture_->getNumCols();

	frame = int((SDL_GetTicks() / timeperframe) % texture_->getNumCols());

	texture_->renderFrame(getRect(), row, frame);
}

Butterfly::~Butterfly() {
	texture_ = nullptr;
}

void Butterfly::update() {
	ArrowsGameObject::update();

	if (static_cast<PlayState*>(state_)->collisionButterfly(this))
		static_cast<PlayState*>(state_)->killButterfly(it_);

	if (rand() % 5 - 1 < 1) {
		if(rand()%2-1 <= 0)
			dir_.setX(-dir_.getX());
		if (rand() % 2 - 1 <= 0)
			dir_.setY(-dir_.getY());
	}
}

void Butterfly::loadFromFile(std::ifstream& file) {}

void Butterfly::saveToFile(std::ofstream& file) {}
