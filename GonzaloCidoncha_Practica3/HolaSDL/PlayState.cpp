#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

PlayState::PlayState(Game* g) : GameState(g) {

	flechasRect = SDL_Rect{ 50, 30, 25, 10 };
	puntRect = SDL_Rect{ 100, 70, 100, 100 };
	level_ = 1;

	bow_ = new Bow(Point2D(10, WIN_HEIGHT / 2), 50, 80, Vector2D(0, 0), nullptr, g_->texturas_[NLBow], g_->texturas_[LBow], g_->texturas_[Arrows], this);
	addGameObject(bow_);
	addEventHandler(bow_);
	score_ = new ScoreBoard(g_->texturas_[Numbers], Point2D(WIN_WIDTH - 200, 20), 50, 50);
	stage_.push_back(score_);

	for (int i = 0; i < 5 + level_; i++) {
		Butterfly* newBut = new Butterfly(rand() % WIN_WIDTH - 0, rand() % WIN_HEIGHT - 0, 80, 80, Vector2D(rand()%2+1, rand()%2+1), g_->texturas_[Butterflies], this);
		butterflies_.push_back(newBut);
		addGameObject(newBut);
	}
	 
}

void PlayState::render() {
	SDL_RenderClear(g_->renderer_);
	g_->backgrounds_[level_%4]->render({ 0,0,WIN_WIDTH,WIN_HEIGHT });
	for (int i = 0; i < arrowsLeft; i++) {
		flechasRect.x = 50 + 25 * i;
		SDL_RenderCopyEx(g_->renderer_, g_->texturas_[Arrows]->getTexture(), NULL, &flechasRect, -90, NULL, SDL_FLIP_NONE);
	}
	GameState::render();
	SDL_RenderPresent(g_->renderer_);
}

void PlayState::handleEvents(SDL_Event evt) {
	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_p) {
			g_->getGSM()->pushState(new PauseState(g_));
		}
	}
	GameState::handleEvents(evt);
}

void PlayState::update() {
	GameState::update();

	if (score_->getPunt() >= 100 * level_) {
		nextLevel();
	}

	if (level_ == 4)
		g_->getGSM()->pushState(new EndState(g_));


	eliminar();
	generate();
}

void PlayState::generate() {
	if (rand() % 100 - 1 <= 3) {
		Balloon* balloon = new Balloon(Point2D(rand() % WIN_WIDTH - 20, WIN_HEIGHT - 10), Vector2D(0, -1), 100, 100, 0, g_->texturas_[Ballons], this);
		balloons_.push_back(balloon);
		addGameObject(balloon);
	}
}

void PlayState::nextLevel() {
	level_++;
	arrowsLeft = 10;

	for (int i = 0; i < 5 + level_; i++) {
		Butterfly* newBut = new Butterfly(rand() % WIN_WIDTH - 0, rand() % WIN_HEIGHT - 0, 80, 80, Vector2D(0, 0), g_->texturas_[Butterflies], this);
		butterflies_.push_back(newBut);
		addGameObject(newBut);
	}

}

bool PlayState::collisionBalloon(Balloon* b) {
	bool aux = false;
	auto it = arrows_.begin();
	while (it != arrows_.end() && !aux) {
		aux = SDL_HasIntersection(&((*it)->getHead()), &b->getRect());
		if (aux) {
			score_->addPunt(10);
			if (rand() % 5 - 1 == 2) {
				Reward* newrew = new Reward(b->getRect().x, b->getRect().y+30, g_->texturas_[Rewards], g_->texturas_[Bubble], this);
				rewards_.push_back(newrew);
				addGameObject(newrew);
				addEventHandler(newrew);
			}
		}
		else it++;
	}
	return aux;
}

bool PlayState::collisionButterfly(Butterfly* b) {
	bool aux = false;
	auto it = arrows_.begin();
	while (it != arrows_.end() && !aux) {
		aux = SDL_HasIntersection(&((*it)->getHead()), &b->getRect());
		if (aux) {
			score_->addPunt(-10);
		}
		else it++;
	}
	return aux;
}

bool PlayState::collisionReward(Reward* b) {
	bool aux = false;
	auto it = arrows_.begin();
	while (it != arrows_.end() && !aux) {
		aux = SDL_HasIntersection(&((*it)->getHead()), &b->getRect());
		it++;
	}
	return aux;
}

void PlayState::killBalloon(list<GameObject*>::iterator it) {
	balloons_.remove(static_cast<Balloon*>((*it)));
	eliminados_.push_back(it);
}

void PlayState::killButterfly(list<GameObject*>::iterator it) {
	butterflies_.remove(static_cast<Butterfly*>((*it)));
	eliminados_.push_back(it);
}

void PlayState::killReward(list<GameObject*>::iterator it, list<EventHandler*>::iterator evtit) {
	rewards_.remove(static_cast<Reward*>((*it)));
	eventHandlers_.remove((*evtit));
	eliminados_.push_back(it);
}

void PlayState::killArrow(list<GameObject*>::iterator it) {
	arrows_.remove(static_cast<Arrow*>((*it)));
	eliminados_.push_back(it);
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
			if (score_->getPunt() > punts[i].second) {
				out << "Jugador " << score_->getPunt() << "\n";
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
	arrows_.clear();
	balloons_.clear();
	butterflies_.clear();
	rewards_.clear();
	eliminados_.clear();
}

void PlayState::extraArrow() {
	if(arrowsLeft<10)
		arrowsLeft += 1;
}

void PlayState::eliminar() {
	auto it = eliminados_.begin();
	while (it != eliminados_.end())
	{
		delete (**it);
		**it = nullptr;
		stage_.erase(*it);
		it++;
	}
	eliminados_.clear();
}

void PlayState::shoot(Arrow* arrow) {
	arrows_.push_back(arrow);
	addGameObject(arrow);
	arrowsLeft--;
}

void PlayState::saveGame(string file) {
	ofstream f;
	f.open(file);

	f << level_ << endl;
	f << score_->getPunt() << endl;
	bow_->saveToFile(f);
	f << endl;
	f << " " << arrowsLeft << endl;
	f << arrows_.size() << endl;
	for (Arrow* arrow : arrows_)
	{
		arrow->saveToFile(f);
		f << std::endl;
	}

	f << balloons_.size() << endl;
	for (Balloon* balloon : balloons_)
	{
		balloon->saveToFile(f);
		f << std::endl;
	}

	f << butterflies_.size() << endl;
	for (Butterfly* but : butterflies_) {
		but->saveToFile(f);
		f << endl;
	}

	f << rewards_.size() << std::endl;
	for (Reward* reward : rewards_)
	{
		reward->saveToFile(f);
		f << std::endl;
	}

	f.close();
}

void PlayState::loadGame(string file) {
	ifstream f;
	f.open(file);

	f >> level_;

	int punt;
	f >> punt;
	score_->setPunt(punt);

	bow_->loadFromFile(f);
	f >> arrowsLeft;

	int flechas;
	f >> flechas;
	for (int i = 0; i < flechas; i++) {
		Arrow* newarrow = new Arrow(Point2D(0, 0), 0, 0, 0, Vector2D(0, 0), g_->texturas_[Arrows], this);
		newarrow->loadFromFile(f);
		arrows_.push_back(newarrow);
		addGameObject(newarrow);
	}

	int globos;
	f >> globos;
	for (int i = 0; i < globos; i++) {
		Balloon* newbal = new Balloon(Point2D(0, 0), Vector2D(0, 0), 100, 100, 0, g_->texturas_[Ballons], this);
		newbal->loadFromFile(f);
		balloons_.push_back(newbal);
		addGameObject(newbal);
	}

	int butterflies;
	f >> butterflies;
	for (int i = 0; i < butterflies; i++) {
		Butterfly* newbut = new Butterfly(0, 0, 80, 80, Vector2D(0, 0), g_->texturas_[Butterflies], this);
		newbut->loadFromFile(f);
		butterflies_.push_back(newbut);
		addGameObject(newbut);
	}

	int rewards;
	f >> rewards;
	for (int i = 0; i < rewards; i++) {
		Reward* newrew = new Reward(0, 0, g_->texturas_[Rewards], g_->texturas_[Bubble], this);
		newrew->loadFromFile(f);
		rewards_.push_back(newrew);
		addGameObject(newrew);
	}

	f.close();
}