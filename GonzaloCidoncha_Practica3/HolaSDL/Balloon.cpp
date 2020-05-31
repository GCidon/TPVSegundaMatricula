#include "Balloon.h"
#include "GameState.h"
#include "PlayState.h"

Balloon::Balloon(Point2D pos, Vector2D dir, int w, int h, double speed, Texture* texture, GameState* state) :
	ArrowsGameObject(pos.x_, pos.y_, dir.getX(), dir.getY(), w, h, 10, 0, texture, state)
{
	color = rand() % 7 - 1;
}

Balloon::~Balloon() {}

void Balloon::render() {
	texture_->renderFrame(getRect(), color, 0);
}

void Balloon::update() {
	if (estado) {
		ArrowsGameObject::update();
		if (static_cast<PlayState*>(state_)->collisionBalloon(this))
			estado = false;
		else if (pos_.x_ > WIN_WIDTH || pos_.x_ < 0 || pos_.y_ > WIN_HEIGHT || pos_.y_ + h_ / 2 < 0)
			estado = false;
	}
	else static_cast<PlayState*>(state_)->killBalloon(it_);
}

void Balloon::loadFromFile(ifstream& file) {
	ArrowsGameObject::loadFromFile(file);
	file >> color;
}

void Balloon::saveToFile(ofstream& file) {
	ArrowsGameObject::saveToFile(file);
	file << color << " ";
}

