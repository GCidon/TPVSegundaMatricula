#include "Game.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("TPV", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) throw "Error loading the SDL window or renderer";

	backgrounds_[0] = new Texture(renderer_, "..//images//Cartoon_Forest_BG_01.png", 1, 1);
	backgrounds_[1] = new Texture(renderer_, "..//images//Cartoon_Forest_BG_02.png", 1, 1);
	backgrounds_[2] = new Texture(renderer_, "..//images//Cartoon_Forest_BG_03.png", 1, 1);
	backgrounds_[3] = new Texture(renderer_, "..//images//Cartoon_Forest_BG_04.png", 1, 1);

	for (int i = 0; i < NUM_TEXTURES; i++) {
		texturas_[i] = new Texture(renderer_, (RUTA + atributes_[i].nombre), atributes_[i].row, atributes_[i].col);
	}

	flechasRect = SDL_Rect{ 50, 30, 25, 10 };
	puntRect = SDL_Rect{ 100, 70, 100, 100 };

	bow_ = new Bow(Point2D(10, WIN_HEIGHT / 2), 50, 80, Vector2D(0, 0), nullptr, texturas_[NLBow], texturas_[LBow], texturas_[Arrows], this);
	score = new ScoreBoard(texturas_[Numbers], Point2D(WIN_WIDTH - 200, 20), 50, 50);
	gameObjects_.push_back(score);

	for (int i = 0; i < 5; i++) {
		gameObjects_.push_back(new Butterfly(rand() % WIN_WIDTH - 0, rand() % WIN_HEIGHT - 0, 80, 80, Vector2D(1, 1), texturas_[Butterflies], this));
	}

	puntuacion = 0;
	level = 1;
}

void Game::render() {
	SDL_RenderClear(renderer_);
	SDL_RenderCopy(renderer_, backgrounds_[level-1]->getTexture(), NULL, NULL);
	// Dibujo del numero de flechas disponibles
	for (int i = 0; i < arrowsLeft; i++) {
		flechasRect.x = 50 + 25 * i;
		SDL_RenderCopyEx(renderer_, texturas_[Arrows]->getTexture(), NULL, &flechasRect, -90, NULL, SDL_FLIP_NONE);
	}
	for (auto obj : gameObjects_) obj->render();
	bow_->render(renderer_);
	for each (auto arrow in arrows_) arrow->render(renderer_);
	for each (auto balloon in balloons_) balloon->render();
	SDL_RenderPresent(renderer_);
}

void Game::handleEvents() {
	SDL_Event evt;
	while (SDL_PollEvent(&evt) && !exit) {
		if (evt.type == SDL_QUIT) exit = true;
		//for each (auto obj in eventHandlers_) obj->handleEvent(evt);
		if (bow_->handleEvents(evt, arrows_)) {
			if(arrowsLeft>0)
				arrowsLeft--;
		}
	}
}

void Game::run() {
	cout << "Inserte su nombre: \n";
	cin >> name;

	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			startTime = SDL_GetTicks();
		}
		render();
	}

	saveGame("scoreboard.txt");
}

void Game::update() {
	for (auto obj : gameObjects_) obj->update();
	bow_->update();

	auto arrow = arrows_.begin();
	while (!arrows_.empty() && arrow != arrows_.end()) {
		bool deleted = false;
		Arrow* aux = *arrow;
		if (aux->update()) {
			arrows_.erase(arrow);
			delete aux;
			arrow = arrows_.begin();
			deleted = true;
			if (arrowsLeft <= 0 && arrows_.size() == 0)
				exit = true;
		}
		if (!arrows_.empty() && !deleted) 
			arrow++;
	}

	auto balloon = balloons_.begin();
	while (!balloons_.empty() && balloon != balloons_.end()) {
		bool deleted = false;
		Balloon* aux = *balloon;
		if (aux->update(arrows_)) {
			if (aux->isHit()) score->addPunt(10);
			balloons_.erase(balloon);
			delete aux;
			balloon = balloons_.begin();
			deleted = true;
		}
		if (!balloons_.empty() && !deleted)
			balloon++;
	}

	if (score->getPunt() >= 100*level) {
		if (level == 4) exit = true;
		else nextLevel();
	}

	generate();
}

Game::~Game() {
	for (int i = 0; i < NUM_TEXTURES; i++) delete texturas_[i];
	for (int i = 0; i < 4; i++) delete backgrounds_[i];
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
		Balloon* aux = *balloon;
		balloons_.erase(balloon);
		delete aux;
		aux = nullptr;
		balloon = balloons_.begin();
	}

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::generate() {
	if (rand() % 100 - 1 <= 3) {
		Balloon* balloon = new Balloon(Point2D(rand() % WIN_WIDTH - 50, WIN_HEIGHT-10), 100, 100, Vector2D(0, -speed), texturas_[Ballons], this);
		balloons_.push_back(balloon);
	}
}

void Game::saveGame(string file) {

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
			out << punts[i - 1].first << " " << punts[i-1].second << "\n";
		}
		i++;
	}
	out.close();

}

void Game::nextLevel() {
	level++;
	arrowsLeft = 10;

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
		Balloon* aux = *balloon;
		balloons_.erase(balloon);
		delete aux;
		aux = nullptr;
		balloon = balloons_.begin();
	}



	for (int i = 0; i < 5*level; i++) {
		gameObjects_.push_back(new Butterfly(rand() % WIN_WIDTH - 0, rand() % WIN_HEIGHT - 0, 80, 80, Vector2D(1, 1), texturas_[Butterflies], this));
	}

}
