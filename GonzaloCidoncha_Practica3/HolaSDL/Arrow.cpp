#include "Arrow.h"
#include "GameState.h"
#include "PlayState.h"

SDL_Rect Arrow::getHead() {
	SDL_Rect ret;
	ret.x = pos_.x_ + (w_ / 2);
	ret.y = pos_.y_;
	ret.w = w_ / 2;
	ret.h = h_;
	return ret;
}

void Arrow::update() {
	ArrowsGameObject::update();

	if (pos_.x_ > WIN_WIDTH || pos_.x_ < 0 || pos_.y_ > WIN_HEIGHT || pos_.y_ < 0)
		static_cast<PlayState*>(state_)->killArrow(it_);
}
