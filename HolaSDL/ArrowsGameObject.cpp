#include "ArrowsGameObject.h"
#include "Game.h"

ArrowsGameObject::ArrowsGameObject(Point2D pos, double w, double h, Vector2D dir, Texture* texture, Game* game) : pos_(pos.x_, pos.y_), dir_(dir.getX(), dir.getY())
{
	w_ = w;
	h_ = h;
	texture_ = texture;
	game_ = game;
}

ArrowsGameObject::~ArrowsGameObject() {
	texture_ = nullptr;
	game_ = nullptr;
}

void ArrowsGameObject::render(SDL_Renderer* renderer) {
	//
}

bool ArrowsGameObject::update() {
	pos_ = Point2D(pos_.x_ + dir_.getX(), pos_.y_ + dir_.getY());

	return false;
}

SDL_Rect ArrowsGameObject::getRect() {
	SDL_Rect ret;
	ret.w = w_;
	ret.h = h_;
	ret.x = pos_.x_;
	ret.y = pos_.y_;
	return ret;
}