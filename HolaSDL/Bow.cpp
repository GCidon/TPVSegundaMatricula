#include "Bow.h"
#include "Game.h"
#include <iostream>

Bow::Bow(Point2D pos, double w, double h, Vector2D dir, Arrow* arrow, Texture* texture, Game* game) :
	pos_(pos), w_(w), h_(h), dir_(dir) 
{
	loadedArrow_ = arrow;
	texture_ = texture;
	game_ = game;
	if (loadedArrow_ != nullptr) loaded = true;
	else loaded = false;
}

Bow::~Bow() {
	texture_ = nullptr;
	game_ = nullptr;
	loadedArrow_ = nullptr;
}

void Bow::render() {

	SDL_Rect destRect;
	destRect.w = w_;
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	texture_->render(destRect);
}

void Bow::setDir(Vector2D newdir) {
	dir_ = newdir;
}

void Bow::update() {
	if (pos_.y_ + dir_.getY()< WIN_HEIGHT-h_ && (pos_.y_ + dir_.getY() > 0))
		pos_ = Point2D(pos_.x_ + dir_.getX(), pos_.y_ + dir_.getY());
}

void Bow::handleEvents(SDL_Event const& evt) {
	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_DOWN) {
			setDir(Vector2D(0, speed));
		} else if (evt.key.keysym.sym == SDLK_UP) {
			setDir(Vector2D(0, -speed));
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			shoot();
		} else if (evt.key.keysym.sym == SDLK_LEFT) {
			load();
		}
	}
	if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_UP || evt.key.keysym.sym == SDLK_DOWN)
			setDir(Vector2D(0, 0));
	}
}

void Bow::load() {
	if (!loaded && loadedArrow_ == nullptr) {
		loaded = true;
		loadedArrow_ = new Arrow(pos_, Vector2D(speed,0), texture_);
	}
}

void Bow::shoot() {
	if (loaded) {
		loadedArrow_->setDir(dir_);
		loaded = false;
	}
}
