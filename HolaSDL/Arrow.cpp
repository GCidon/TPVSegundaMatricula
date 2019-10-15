#include "Arrow.h"
#include "Game.h"

void Arrow::render() {
	SDL_Rect ret;
	ret.x = pos_.x_;
	ret.y = pos_.y_;
	ret.w = texture_->getW();
	ret.h = texture_->getH();
	texture_->render(ret);
}

SDL_Rect Arrow::getPunta() {
	SDL_Rect punta;
	punta.x = pos_.x_ + (texture_->getW() * 0.75);
	punta.y = pos_.y_;
	punta.w = texture_->getW() / 4;
	punta.h = texture_->getH();
	return punta;
}

void Arrow::setDir(Vector2D newdir) {
	dir_ = newdir;
}

bool Arrow::update() {
	pos_ = Point2D(pos_.x_ + dir_.getX(), pos_.y_ + dir_.getY());

	if (pos_.x_ > WIN_WIDTH || pos_.x_ < 0 || pos_.y_ > WIN_HEIGHT || pos_.y_ < 0)
		return true;
	else return false;
}
