#include "ArrowsGameObject.h"
#include "Game.h"

SDL_Rect ArrowsGameObject::getRect() {
	SDL_Rect ret;
	ret.w = w_;
	ret.h = h_;
	ret.x = pos_.x_;
	ret.y = pos_.y_;
	return ret;
}

ArrowsGameObject::ArrowsGameObject(double x, double y, double w, double h, Vector2D dir, Texture* texture, Game* game) :
	pos_(x, y), w_(w), h_(h), dir_(dir) 
{
	texture_ = texture;
	game_ = game;
}

void ArrowsGameObject::render() {
	SDL_Rect destRect;
	destRect.w = w_;
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	texture_->render(destRect);
}

void ArrowsGameObject::update() {
	pos_ = Point2D(pos_.x_ + dir_.getX(), pos_.y_ + dir_.getY());
}

void ArrowsGameObject::setItList(list<GameObject*>::iterator it) {
	it_ = it;
}
