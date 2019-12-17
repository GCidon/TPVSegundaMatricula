#include "SDLGameObject.h"

SDLGameObject::SDLGameObject(Point2D pos, int w, int h, Texture* texture) : GameObject(), pos_(pos){
	w_ = w;
	h_ = h;
	texture_ = texture;
}

void SDLGameObject::render() {
	texture_->render(getRect());
}

SDL_Rect SDLGameObject::getRect() {
	SDL_Rect rect;
	rect.x = pos_.x_;
	rect.y = pos_.y_;
	rect.w = w_;
	rect.h = h_;
	return rect;
}
