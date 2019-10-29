#include "Balloon.h"
#include "Game.h"

Balloon::Balloon(Point2D pos, double w, double h, Vector2D dir, Texture* texture, Game* game) :
	pos_(pos), w_(w), h_(h), dir_(dir)
{
	color = rand() % 7 - 1;
	texture_ = texture;
	game_ = game;
}

void Balloon::render() {
	SDL_Rect destRect;
	destRect.w = w_;
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	texture_->renderFrame(destRect, color, deadCount);
}

SDL_Rect Balloon::getRect() {
	SDL_Rect ret;
	ret.w = w_;
	ret.h = h_;
	ret.x = pos_.x_;
	ret.y = pos_.y_;
	return ret;
}

bool Balloon::update(vector<Arrow*> arrows) {
	pos_ = Point2D(pos_.x_ + dir_.getX(), pos_.y_ + dir_.getY());

	int i = 0;
	// Comprueba si las esquinas frontales de la cabeza de la flecha estan dentro del rectangulo del globo
	while (!arrows.empty() && i < arrows.size()) {
		SDL_Rect head = arrows.at(i)->getHead();
		if (head.x + head.w > pos_.x_ && head.x + head.w < pos_.x_+w_ && head.y > pos_.y_ && head.y < pos_.y_ + h_ ||
			head.x + head.w > pos_.x_ && head.x + head.w < pos_.x_ + w_ && head.y + head.h > pos_.y_ && head.y + head.h < pos_.y_ + h_)
			hit = true;
		i++;
	}
	
	if (pos_.x_ > WIN_WIDTH || pos_.x_ < 0 || pos_.y_ > WIN_HEIGHT || pos_.y_+h_/2 < 0)
		return true;
	// Contador de frames de animacion de explosion
	else if (hit) {
		deadCount++;
		if(deadCount==4)
			return true;
	}
	else return false;
}
