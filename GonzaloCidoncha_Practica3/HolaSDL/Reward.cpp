#include "Reward.h"
#include "Game.h"
#include "PlayState.h"

Reward::Reward(double x, double y, Texture* texture, Texture* burbuja, GameState* state) :
	ArrowsGameObject(x, y, 0, 2, 40, 20, 20, 0, texture, state) 
{
	burbujaText = burbuja;
	type_ = rand() % 2 + 1;
	burbuja_ = true;
}

void Reward::render() {
	texture_->renderFrame(getRect(), type_ + 1, 1);
	if (burbuja_) burbujaText->renderFrame(getRect(), 0, 0);
}

void Reward::update() {
	ArrowsGameObject::update();

	if (burbuja_){
		if (static_cast<PlayState*>(state_)->collisionReward(this))
			burbuja_ = false;
	}

	if (pos_.y_ > WIN_HEIGHT)
		static_cast<PlayState*>(state_)->killReward(it_);
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
