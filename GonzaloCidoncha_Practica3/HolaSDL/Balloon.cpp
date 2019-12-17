#include "Balloon.h"
#include "Game.h"

Balloon::Balloon(Point2D pos, double w, double h, Vector2D dir, Texture* texture, Game* game) :
	ArrowsGameObject(pos.x_, pos.y_, w, h, dir, texture, game)
{
	color = rand() % 7 - 1;
}

Balloon::~Balloon() {
	texture_ = nullptr;
	game_ = nullptr;
}

void Balloon::render() {
	SDL_Rect destRect;
	destRect.w = w_;
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	texture_->renderFrame(destRect, color, deadCount);
}

void Balloon::update() {
	ArrowsGameObject::update();
	
	if (pos_.x_ > WIN_WIDTH || pos_.x_ < 0 || pos_.y_ > WIN_HEIGHT || pos_.y_ + h_ / 2 < 0)
		hit = true;
}
