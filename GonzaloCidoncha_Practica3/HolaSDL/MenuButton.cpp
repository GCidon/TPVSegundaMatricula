#include "MenuButton.h"

MenuButton::MenuButton(Point2D pos, int w, int h, Texture* texture, Game* g, CallBackOnClick* callback) : SDLGameObject(pos, w, h, texture, nullptr) {
	g_ = g;
	cb_ = callback;
}

bool MenuButton::handleEvent(SDL_Event const& evt) {
	if (evt.type == SDL_MOUSEBUTTONUP && evt.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p = { evt.button.x, evt.button.y };
		SDL_Rect r = { pos_.x_, pos_.y_, w_, h_ };

		if (SDL_PointInRect(&p, &r)) {
			cb_(g_);
		}
	}
	return true;
}
