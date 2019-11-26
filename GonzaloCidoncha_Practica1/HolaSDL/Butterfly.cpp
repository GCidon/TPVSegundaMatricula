#include "Butterfly.h"
#include "Game.h"

void Butterfly::render() {
	SDL_Rect destRect;
	destRect.w = w_;
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	if (col < 10) col++;
	else {
		if (row < 4) row++;
		else row = 0;
		col = 0;
	}

	texture_->renderFrame(destRect, row, col);
}

bool Butterfly::update() {
	ArrowsGameObject::update();

	if (rand() % 100 - 1 < 3) dir_ = Vector2D(-dir_.getX(), -dir_.getY());
	return false;
}
