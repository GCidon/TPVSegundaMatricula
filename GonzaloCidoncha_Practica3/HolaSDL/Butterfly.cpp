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

	if (rand() % 100 - 1 < 3) dir_ = Vector2D(-dir_.getX(), -dir_.getY());
}

void Butterfly::loadFromFile(std::ifstream& file) {

}

void Butterfly::saveToFile(std::ofstream& file) {

}
