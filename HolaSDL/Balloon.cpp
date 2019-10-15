#include "Balloon.h"
#include "Game.h"

Balloon::Balloon(Point2D pos, double w, double h, Vector2D dir, Texture* texture, Game* game) :
	pos_(pos), w_(w), h_(h), dir_(dir)
{
	texture_ = texture;
	game_ = game;
}

void Balloon::render() {
	SDL_Rect destRect;
	destRect.w = w_;
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	texture_->renderFrame(destRect, 0, 0);
}

bool Balloon::update() {
	pos_ = Point2D(pos_.x_ + dir_.getX(), pos_.y_ + dir_.getY());
	
	if (pos_.x_ > WIN_WIDTH || pos_.x_ < 0 || pos_.y_ > WIN_HEIGHT || pos_.y_ < 0)
		return true;
	else return false;
}
