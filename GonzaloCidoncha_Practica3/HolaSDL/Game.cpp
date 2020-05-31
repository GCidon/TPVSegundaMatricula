#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"

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

	gsm = new GameStateMachine();

	gsm->pushState(new MainMenuState(this));

}

Game::~Game() {
	for (int i = 0; i < NUM_TEXTURES; i++) delete texturas_[i];
	for (int i = 0; i < 4; i++) delete backgrounds_[i];

	delete gsm;
	gsm = nullptr;

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::render() {
	SDL_RenderClear(renderer_);
	gsm->currentState()->render();
	SDL_RenderPresent(renderer_);
}
void Game::update() {
	gsm->currentState()->update();
}
void Game::handleEvents() {
	SDL_Event evt;
	while (SDL_PollEvent(&evt) && !exit) {
		gsm->currentState()->handleEvents(evt);
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
