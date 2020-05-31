#include "ArrowsGameObject.h"

#include "GameState.h"

ArrowsGameObject::ArrowsGameObject(double posx, double posy, double dirx, double diry, int w, int h, double speed, int angulo, Texture* texture, GameState* state) :
	SDLGameObject(Point2D(posx, posy), w, h, texture, state), dir_(dirx, diry)
{
	speed_ = speed;
	angulo_ = angulo;
}

void ArrowsGameObject::update() {
	Point2D newpos = Point2D(dir_.getX() * speed_, dir_.getY() * speed_);
	pos_ = pos_ + newpos;
}

void ArrowsGameObject::render() {
	texture_->renderFrame(getRect(), 0, 0, angulo_);
}

void ArrowsGameObject::setItList(const list<GameObject*>::iterator& it) {
	it_ = it;
}

void ArrowsGameObject::loadFromFile(std::ifstream& file) {
	file >> pos_.x_ >> pos_.y_ >> dir_ >> speed_ >> w_ >> h_ >> angulo_;
}

void ArrowsGameObject::saveToFile(std::ofstream& file) {
	file << pos_.x_ << " " << pos_.y_ << " " << dir_.getX() << " " << dir_.getY() << " " << speed_ << " " << w_ << " " << h_ << " " << angulo_ << " ";
}

SDL_Rect ArrowsGameObject::getRect() const {
	SDL_Rect ret;
	ret.x = pos_.x_;
	ret.y = pos_.y_;
	ret.w = w_;
	ret.h = h_;
	return ret;
}