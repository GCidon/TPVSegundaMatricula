#include "Reward.h"
#include "Game.h"

Reward::Reward(double x, double y, Texture* texture, Texture* bubble, Game* game) :
	ArrowsGameObject(x, y, 40, 20, Vector2D(0, 2), texture, game) 
{
	bubbleText = bubble;
	type = rand() % 4 - 1;
}

void Reward::render() {
	SDL_Rect mainrect;

	mainrect.x = pos_.x_+20;
	mainrect.y = pos_.y_+30;
	mainrect.w = w_;
	mainrect.h = h_;

	SDL_Rect rect;

	rect.x = pos_.x_;
	rect.y = pos_.y_;
	rect.w = w_*2;
	rect.h = h_*4;

	texture_->renderFrame(mainrect, type, 1);
	if(inBubble) bubbleText->render(rect);
}

void Reward::update() {
	ArrowsGameObject::update();
}

bool Reward::handleEvent(SDL_Event const& evt) {
	return false;
}
