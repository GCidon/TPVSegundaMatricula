#include "ScoreBoard.h"

// Coloca tres cifras en funcion de la puntuacion, por si supera 100 puntos
void ScoreBoard::render(SDL_Renderer* renderer) {
	SDL_Rect rectLL;
	rectLL.w = w_;
	rectLL.h = h_;
	rectLL.x = pos_.x_;
	rectLL.y = pos_.y_;

	SDL_Rect rectL;
	rectL.w = w_;
	rectL.h = h_;
	rectL.x = pos_.x_ + w_/2 + 10;
	rectL.y = pos_.y_;

	SDL_Rect rectR;
	rectR.w = w_;
	rectR.h = h_;
	rectR.x = pos_.x_ + w_ + 20;
	rectR.y = pos_.y_;


	if (punt >= 100) {
		texture_->renderFrame(rectLL, 0, 1);
		texture_->renderFrame(rectL, 0, (punt-100)/10);
	}

	else {
		texture_->renderFrame(rectLL, 0, 0);
		texture_->renderFrame(rectL, 0, punt / 10);
	}
	
	texture_->renderFrame(rectR, 0, 0);
	
}
