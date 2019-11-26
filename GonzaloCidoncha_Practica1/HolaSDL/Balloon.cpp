#include "Balloon.h"
#include "Game.h"

Balloon::Balloon(Point2D pos, double w, double h, Vector2D dir, Texture* texture, Game* game) :
	ArrowsGameObject(pos.x_, pos.y_, w, h, dir, texture, game)
{
	color = rand() % 7 - 1;
}

Balloon::~Balloon() {
	texture_ = nullptr;
	game_ = nullptr;
}

void Balloon::render() {
	SDL_Rect destRect;
	destRect.w = w_;
	destRect.h = h_;
	destRect.x = pos_.x_;
	destRect.y = pos_.y_;

	texture_->renderFrame(destRect, color, deadCount);
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
