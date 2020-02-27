#include "Reward.h"
#include "Game.h"
#include "PlayState.h"

Reward::Reward(double x, double y, Texture* texture, PlayState* ps, Game* game) :
	ArrowsGameObject(x, y, 40, 20, Vector2D(0, 2), texture, game) 
{
	playstate = ps;
	type = rand() % 2 + 1;
}

void Reward::render() {

	SDL_Rect rect;

	rect.x = pos_.x_;
	rect.y = pos_.y_;
	rect.w = w_;
	rect.h = h_;

	texture_->renderFrame(rect, type+1, 1);
}

void Reward::update() {
	ArrowsGameObject::update();

	if (pos_.y_ > WIN_HEIGHT)
		hit = true;
}

bool Reward::handleEvent(SDL_Event const& evt) {
	if (evt.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool aux1 = x > pos_.x_;
		bool aux2 = x < pos_.x_ + w_;
		bool aux3 = y > pos_.y_;
		bool aux4 = y < pos_.y_ + h_;
		if (aux1 && aux2 && aux3 && aux4) {
			switch (type) {
			case 1:
				playstate->extraArrow();
				break;
			case 2:
				break;
			}
			hit = true;
		}
	}
	return false;
}
