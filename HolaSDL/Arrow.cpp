#include "Arrow.h"
#include "Game.h"

void Arrow::render() {
	SDL_Rect ret;
	ret.x = pos_.x_;
	ret.y = pos_.y_;
	ret.w = w_;
	ret.h = h_;
	return ret;
}

SDL_Rect Arrow::getHead() {
	SDL_Rect ret;
	ret.x = pos_.x_ + (w_ / 2);
	ret.y = pos_.y_;
	ret.w = w_ / 2;
	ret.h = h_;
	return ret;
}

void Arrow::setDir(Vector2D newdir) {
	dir_ = newdir;
}

void Arrow::setPos(Point2D newpos) {
	pos_ = newpos;
}

bool Arrow::update() {
	pos_ = Point2D(pos_.x_ + dir_.getX(), pos_.y_ + dir_.getY());

	if (pos_.x_ > WIN_WIDTH || pos_.x_ < 0 || pos_.y_ > WIN_HEIGHT || pos_.y_ < 0)
		return true;
	else return false;
}
