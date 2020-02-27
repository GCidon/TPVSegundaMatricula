#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

PlayState::PlayState(Game* g) : GameState(g) {

	flechasRect = SDL_Rect{ 50, 30, 25, 10 };
	puntRect = SDL_Rect{ 100, 70, 100, 100 };

	bow_ = new Bow(Point2D(10, WIN_HEIGHT / 2), 50, 80, Vector2D(0, 0), nullptr, g_->texturas_[NLBow], g_->texturas_[LBow], g_->texturas_[Arrows], g_);
	stage.push_back(bow_);
	eventHandlers_.push_back(bow_);
	bow_->setItList(stage.end());
	score = new ScoreBoard(g_->texturas_[Numbers], Point2D(WIN_WIDTH - 200, 20), 50, 50);
	stage.push_back(score);
	score->setItList(stage.end());

	for (int i = 0; i < 5; i++) {
		Butterfly* newBut = new Butterfly(rand() % WIN_WIDTH - 0, rand() % WIN_HEIGHT - 0, 80, 80, Vector2D(1, 1), g_->texturas_[Butterflies], g_);
		butterflies_.push_back(newBut);
		stage.push_back(newBut);
		newBut->setItList(stage.end());
	}

	puntuacion = 0;
	level = 1;
}

void PlayState::render() {
	SDL_RenderClear(g_->renderer_);
	SDL_RenderCopy(g_->renderer_, g_->backgrounds_[level - 1]->getTexture(), NULL, NULL);
	// Dibujo del numero de flechas disponibles
	for (int i = 0; i < arrowsLeft; i++) {
		flechasRect.x = 50 + 25 * i;
		SDL_RenderCopyEx(g_->renderer_, g_->texturas_[Arrows]->getTexture(), NULL, &flechasRect, -90, NULL, SDL_FLIP_NONE);
	}
	for (auto obj : stage) obj->render();
	for each (auto arrow in arrows_) arrow->render(g_->renderer_);
	for each (auto but in butterflies_) but->render();
	SDL_RenderPresent(g_->renderer_);
}

void PlayState::handleEvents(SDL_Event evt) {
	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_p) {
			g_->getGSM()->pushState(new PauseState(g_));
		}
		else if (evt.key.keysym.sym == SDLK_q) {
			g_->getGSM()->pushState(new EndState(g_));
		}
		else if (evt.key.keysym.sym == SDLK_RIGHT) {
			shoot();
		}
	}
	for each (auto obj in eventHandlers_) obj->handleEvent(evt);
}

void PlayState::update() {
	for (auto obj : stage) obj->update();

	auto bal = balloons_.begin();
	bool deleted = false;
	while (bal != balloons_.end() && !deleted) {
		Balloon* aux = *bal;
		for (auto arrow : arrows_) {
			if (collisionA(arrow, aux)) {
				score->addPunt(10);
				Point2D newpos(aux->getPos().x_+aux->getW()/3, aux->getPos().y_);
				reward(newpos);
			}
		}
		if (aux->hit) {
			balloons_.remove(aux);
			eliminated_.push_back(aux);
			bal = balloons_.begin();
			deleted = true;
		}
		if (!balloons_.empty() && !deleted)
			bal++;
	}

	auto but = butterflies_.begin();
	deleted = false;
	while (but != butterflies_.end() && !deleted) {
		Butterfly* aux = *but;
		for (auto arrow : arrows_) {
			if (collisionA(arrow, aux) && score->getPunt() > 0) score->addPunt(-10);
		}
		if (aux->hit) {
			butterflies_.remove(aux);
			eliminated_.push_back(aux);
			but = butterflies_.begin();
			deleted = true;
		}
		if (!butterflies_.empty() && !deleted)
			but++;
	}

	auto rew = rewards_.begin();
	deleted = false;
	while (rew != rewards_.end() && !deleted) {
		Reward* aux = *rew;
		if (aux->hit) {
			rewards_.remove(aux);
			eventHandlers_.remove(aux);
			eliminated_.push_back(aux);
			rew = rewards_.begin();
			deleted = true;
		}
		if (!rewards_.empty() && !deleted)
			rew++;
	}

	auto obj = eliminated_.begin();
	while (obj != eliminated_.end()) {
		ArrowsGameObject* aux = *obj;
		stage.remove(aux);
		delete aux;
		eliminated_.remove(aux);
		obj = eliminated_.begin();
	}

	if (score->getPunt() >= 100 * level) {
		if (level == 4) g_->getGSM()->pushState(new EndState(g_));
		else nextLevel();
	}

	generate();
}

void PlayState::generate() {
	if (rand() % 100 - 1 <= 3) {
		Balloon* balloon = new Balloon(Point2D(rand() % WIN_WIDTH - 50, WIN_HEIGHT - 10), 100, 100, Vector2D(0, -speed), g_->texturas_[Ballons], g_);
		balloons_.push_back(balloon);
		stage.push_back(balloon);
		auto it = stage.begin();
		int i = 0;
		while (i < stage.size() - 1)
		{
			i++;
			it++;
		}
		balloon->setItList(it);
	}
}


void PlayState::nextLevel() {
	level++;
	arrowsLeft = 10;

	auto arrow = arrows_.begin();
	while (arrow != arrows_.end()) {
		Arrow* aux = *arrow;
		arrows_.erase(arrow);
		stage.remove(aux);
		delete aux;
		aux = nullptr;
		arrow = arrows_.begin();
	}

	auto balloon = balloons_.begin();
	while (!balloons_.empty() && balloon != balloons_.end()) {
		ArrowsGameObject* aux = *balloon;
		balloons_.erase(balloon);
		stage.remove(aux);
		delete aux;
		aux = nullptr;
		balloon = balloons_.begin();
	}

	auto but = butterflies_.begin();
	while (!butterflies_.empty() && but != butterflies_.end()) {
		Butterfly* aux = *but;
		butterflies_.erase(but);
		stage.remove(aux);
		delete aux;
		aux = nullptr;
		but = butterflies_.begin();
	}

	for (int i = 0; i < 5 + level; i++) {
		Butterfly* newBut = new Butterfly(rand() % WIN_WIDTH - 0, rand() % WIN_HEIGHT - 0, 80, 80, Vector2D(1, 1), g_->texturas_[Butterflies], g_);
		butterflies_.push_back(newBut);
		stage.push_back(newBut);
		newBut->setItList(stage.end());
	}

}

void PlayState::shoot() {
	if (bow_->isLoaded()) {
		Arrow* newArrow = new Arrow(Point2D(bow_->getPos().x_, bow_->getPos().y_ + 30), 75, 20, bow_->getAngle(), Vector2D(speed * 3, bow_->getAngle()).normalize() * speed, g_->texturas_[Arrows]);
		stage.push_back(newArrow);
		arrows_.push_back(newArrow);
		newArrow->setItList(stage.end());
		if (arrowsLeft > 0)
			arrowsLeft--;
	}
}

bool PlayState::collisionA(Arrow* hitter, ArrowsGameObject* hitted) {
	SDL_Rect head = hitter->getHead();
	if (head.x + head.w > hitted->getPos().x_ && head.x + head.w < hitted->getPos().x_ + hitted->getW() && head.y > hitted->getPos().y_ && head.y < hitted->getPos().y_ + hitted->getH() ||
		head.x + head.w > hitted->getPos().x_ && head.x + head.w < hitted->getPos().x_ + hitted->getW() && head.y + head.h > hitted->getPos().y_ && head.y + head.h < hitted->getPos().y_ + hitted->getH()) {
		hitted->hit = true;
		return true;
	}
	return false;
}

void PlayState::killObject(list<GameObject*>::iterator it) {
	stage.erase(it);
}

void PlayState::savePunt(string file) {

	ifstream input;
	input.open(file);
	pair<string, int> punts[10];
	for (int i = 0; i < 10; i++) {
		input >> punts[i].first >> punts[i].second;
	}
	input.close();

	ofstream out;
	out.open(file);
	bool written = false;
	int i = 0;
	while (i < 10) {
		if (!written) {
			if (score->getPunt() > punts[i].second) {
				out << name << " " << score->getPunt() << "\n";
				written = true;
			}
			else out << punts[i].first << " " << punts[i].second << "\n";
		}
		else {
			out << punts[i - 1].first << " " << punts[i - 1].second << "\n";
		}
		i++;
	}
	out.close();

}

PlayState::~PlayState() {
	delete bow_;
	bow_ = nullptr;
	delete score;
	score = nullptr;

	auto arrow = arrows_.begin();
	while (arrow != arrows_.end()) {
		Arrow* aux = *arrow;
		arrows_.erase(arrow);
		delete aux;
		aux = nullptr;
		arrow = arrows_.begin();
	}

	auto balloon = balloons_.begin();
	while (!balloons_.empty() && balloon != balloons_.end()) {
		ArrowsGameObject* aux = *balloon;
		balloons_.erase(balloon);
		delete aux;
		aux = nullptr;
		balloon = balloons_.begin();
	}

	auto but = butterflies_.begin();
	while (!butterflies_.empty() && but != butterflies_.end()) {
		Butterfly* aux = *but;
		butterflies_.erase(but);
		delete aux;
		aux = nullptr;
		but = butterflies_.begin();
	}
}

void PlayState::reward(Point2D pos) {
	if (rand()%3+1 == 2) {
		Reward* newreward = new Reward(pos.x_, pos.y_, g_->texturas_[Rewards], this, g_);
		stage.push_back(newreward);
		eventHandlers_.push_back(newreward);
		rewards_.push_back(newreward);
	}
}

void PlayState::extraArrow() {
	if(arrowsLeft<10)
		arrowsLeft += 1;
}