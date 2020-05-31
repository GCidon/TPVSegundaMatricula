#include "Reward.h"
#include "Game.h"
#include "PlayState.h"

Reward::Reward(double x, double y, Texture* texture, Texture* burbuja, GameState* state) :
	ArrowsGameObject(x, y, 0, 1, 40, 20, 5, 0, texture, state) 
{
	burbujaText = burbuja;
	type_ = rand() % 2 + 1;
	burbuja_ = true;
	dead = false;
}

void Reward::render() {
	texture_->renderFrame(getRect(), type_ + 1, 1);
	if (burbuja_) {
		SDL_Rect aux;
		aux.x = pos_.x_-7;
		aux.y = pos_.y_-15;
		aux.w = 50;
		aux.h = 50;
		burbujaText->renderFrame(aux, 0, 0);
	}
}

void Reward::update() {
	ArrowsGameObject::update();

	if (burbuja_){
		if (static_cast<PlayState*>(state_)->collisionReward(this))
			burbuja_ = false;
	}

	if (pos_.y_ > WIN_HEIGHT || dead)
		static_cast<PlayState*>(state_)->killReward(it_, ithandlers_);
}

bool Reward::handleEvent(SDL_Event const& evt) {
	if (!burbuja_) {
		if (evt.type == SDL_MOUSEBUTTONDOWN) {
			SDL_Point point;
			SDL_GetMouseState(&point.x, &point.y);
			if (SDL_PointInRect(&point, &getRect())) {
				switch (type_) {
				case 1:
					static_cast<PlayState*>(state_)->extraArrow();
					break;
				case 2:
					static_cast<PlayState*>(state_)->nextLevel();
					break;
				}
				dead = true;
				return true;
			}
		}
	}
	else return false;
}

void Reward::loadFromFile(ifstream& file) {
	ArrowsGameObject::loadFromFile(file);
	file >> type_ >> burbuja_;
}

void Reward::saveToFile(ofstream& file) {
	ArrowsGameObject::saveToFile(file);
	file << type_ << " " << burbuja_ << " ";
}
