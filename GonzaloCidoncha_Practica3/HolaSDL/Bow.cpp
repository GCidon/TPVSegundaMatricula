#include "Bow.h"
#include "GameState.h"
#include "PlayState.h"
#include <iostream>

Bow::Bow(Point2D pos, double w, double h, Vector2D dir, Arrow* arrow, Texture* texture, Texture* textureL, Texture* arrowTex, GameState* state) :
	ArrowsGameObject(pos.x_, pos.y_, dir.getX(), dir.getY(), w, h, 10, 0, texture, state)
{
	loadedArrow_ = arrow;
	textureL_ = textureL;
	arrowText_ = arrowTex;
	loaded = false;
}

void Bow::render() {

	SDL_Rect destRect;
	
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	if (loaded) {
		destRect.w = w_+20;
		textureL_->renderFrame(destRect, 0, 0, angulo_);
	}
	else {
		destRect.w = w_;
		texture_->renderFrame(destRect, 0, 0, angulo_);
	}
}

void Bow::setDir(Vector2D newdir) {
	dir_ = newdir;
}

void Bow::update() {
	if (pos_.y_ + dir_.getY()< WIN_HEIGHT-h_ && (pos_.y_ + dir_.getY() > 0))
		pos_ = Point2D(pos_.x_ + dir_.getX(), pos_.y_ + dir_.getY());
}

bool Bow::handleEvent(SDL_Event const& evt) {
	bool aux = false;
	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_DOWN) {
			setDir(Vector2D(0, speed*2));
		} else if (evt.key.keysym.sym == SDLK_UP) {
			setDir(Vector2D(0, -speed*2));
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			aux = shoot();
		} else if (evt.key.keysym.sym == SDLK_LEFT) {
			load();
		} else if (evt.key.keysym.sym == SDLK_w) {
			angulo_ -= 5;
		} else if (evt.key.keysym.sym == SDLK_s) {
			angulo_ += 5;
		}
	}
	if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_UP || evt.key.keysym.sym == SDLK_DOWN)
			setDir(Vector2D(0, 0));
	}
	return aux;
}

void Bow::load() {
	if (!loaded && loadedArrow_ == nullptr) {
		loaded = true;
	}
}

bool Bow::shoot() {
	bool aux = false;
	if (loaded) {
		Point2D shootpos = Point2D(pos_.x_, pos_.y_ + (h_ / 2));
		loadedArrow_ = new Arrow(shootpos, 75, 20, angulo_, Vector2D(1, 0), arrowText_, state_);
		static_cast<PlayState*>(state_)->shoot(loadedArrow_);
		loaded = false;
		loadedArrow_ = nullptr;
		aux = true;
	}
	return aux;
}

bool Bow::isLoaded() {
	return loaded;
}
