#include "Game.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("TPV", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) throw "Error loading the SDL window or renderer";

	for (int i = 0; i < NUM_TEXTURES; i++) {
		texturas_[i] = new Texture(renderer_, (RUTA + atributes_[i].nombre), atributes_[i].row, atributes_[i].col);
	}

	bow_ = new Bow(Point2D(10, WIN_HEIGHT/2), 60, 90, Vector2D(0, 0), nullptr, texturas_[NLBow], this);

	background_ = new Balloon(Point2D(0, 0), WIN_WIDTH, WIN_HEIGHT, Vector2D(0, 0), texturas_[Background], this);

	puntuacion = 0;
}

void Game::render() const {
	SDL_RenderClear(renderer_);
	background_->render();
	bow_->render();
	for each (auto arrow in arrows_) arrow->render();
	for each (auto balloon in balloons_) balloon->render();
	SDL_RenderPresent(renderer_);
}

void Game::handleEvents() {
	SDL_Event evt;
	while (SDL_PollEvent(&evt) && !exit) {
		if (evt.type == SDL_QUIT) exit = true;
		bow_->handleEvents(evt);
	}
}

void Game::run() {
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
}

void Game::update() {
	bow_->update();
	for each (auto arrow in arrows_) arrow->update();
	for each (auto balloon in balloons_) balloon->update();
	generate();
}

Game::~Game() {
	for (int i = 0; i < NUM_TEXTURES; i++) delete texturas_[i];
	delete bow_;
	delete background_;
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::generate() {
	if (rand() % 100 - 1 <= 3) {
		Balloon* balloon = new Balloon(Point2D(rand() % WIN_WIDTH - 20, WIN_HEIGHT-10), 50, 50, Vector2D(0, -speed), texturas_[Ballons], this);
		balloons_.push_back(balloon);
	}
}
