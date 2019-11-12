#include "Bow.h"
#include <iostream>
#include "Game.h"

Bow::Bow(Point2D pos, double w, double h, Vector2D dir, Arrow* arrow, Texture* texture, Texture* textureL, Texture* arrowTex, Game* game) :
	ArrowsGameObject(pos, w, h, dir, texture, game)
{
	loadedArrow_ = arrow;
	textureL_ = textureL;
	arrowText_ = arrowTex;
	loaded = false;
}

void Bow::render(SDL_Renderer* renderer) {

	SDL_Rect destRect;
	
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	if (loaded) {
		destRect.w = w_+20;
		//textureL_->render(destRect);
		SDL_RenderCopyEx(renderer, textureL_->getTexture(), NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
	}
	else {
		destRect.w = w_;
		//texture_->render(destRect);
		SDL_RenderCopyEx(renderer, texture_->getTexture(), NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
	}
}

void Bow::setDir(Vector2D newdir) {
	dir_ = newdir;
}

bool Bow::update() {
	if (pos_.y_ + dir_.getY() < WIN_HEIGHT - h_ && (pos_.y_ + dir_.getY() > 0))
		ArrowsGameObject::update();
	return false;
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
		} else if (evt.key.keysym.sym == SDLK_w) {
			angle -= 5;
		} else if (evt.key.keysym.sym == SDLK_s) {
			angle += 5;
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
		loadedArrow_ = new Arrow(pos_, 75, 20, angle, Vector2D(0, 0), arrowText_);
	}
}

// Dispara la flecha guardada y la a�ade al vector de flechas en pantalla
void Bow::shoot(vector<Arrow*>& arrows) {
	if (loaded) {
		loadedArrow_->setPos(Point2D(pos_.x_, pos_.y_ + h_/2));
		Vector2D shootAngle = Vector2D(speed * 3, angle).normalize();
		loadedArrow_->setDir(shootAngle*speed);
		loaded = false;
		arrows.push_back(loadedArrow_);
		loadedArrow_ = nullptr;
	}
}
