#include "Bow.h"
#include "Game.h"
#include <iostream>

Bow::Bow(Point2D pos, double w, double h, Vector2D dir, Arrow* arrow, Texture* texture, Texture* textureL, Texture* arrowTex, Game* game) :
	pos_(pos), w_(w), h_(h), dir_(dir) 
{
	loadedArrow_ = arrow;
	texture_ = texture;
	textureL_ = textureL;
	arrowText_ = arrowTex;
	game_ = game;
	loaded = false;
}

Bow::~Bow() {
	texture_ = nullptr;
	game_ = nullptr;
	loadedArrow_ = nullptr;
}

void Bow::render() {

	SDL_Rect destRect;
	
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	if (loaded) {
		destRect.w = w_+20;
		textureL_->render(destRect);
	}
	else {
		destRect.w = w_;
		texture_->render(destRect);
	}
}

void Bow::setDir(Vector2D newdir) {
	dir_ = newdir;
}

void Bow::update() {
	if (pos_.y_ + dir_.getY()< WIN_HEIGHT-h_ && (pos_.y_ + dir_.getY() > 0))
		pos_ = Point2D(pos_.x_ + dir_.getX(), pos_.y_ + dir_.getY());
}

bool Bow::handleEvents(SDL_Event const& evt, vector<Arrow*>& arrows) {
	bool aux = false;
	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_DOWN) {
			setDir(Vector2D(0, speed*2));
		} else if (evt.key.keysym.sym == SDLK_UP) {
			setDir(Vector2D(0, -speed*2));
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			shoot(arrows);
			aux = true;
		} else if (evt.key.keysym.sym == SDLK_LEFT) {
			load();
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
		loadedArrow_ = new Arrow(pos_, 75, 20, Vector2D(0, 0), arrowText_);
	}
}

// Dispara la flecha guardada y la a�ade al vector de flechas en pantalla
void Bow::shoot(vector<Arrow*>& arrows) {
	if (loaded) {
		loadedArrow_->setPos(Point2D(pos_.x_, pos_.y_ + h_/2));
		loadedArrow_->setDir(Vector2D(speed*3, 0));
		loaded = false;
		arrows.push_back(loadedArrow_);
		loadedArrow_ = nullptr;
	}
}
