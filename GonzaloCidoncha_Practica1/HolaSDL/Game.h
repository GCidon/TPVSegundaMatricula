#pragma once

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "checkML.h"
#include "Texture.h"
#include "Bow.h"
#include "Balloon.h"
#include "Butterfly.h"
#include "ScoreBoard.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

const enum TexturesName{LBow, NLBow, Arrows, Ballons, Background, Numbers, Butterflies};
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int NUM_TEXTURES = 7;
const string RUTA = "..\\images\\";
const uint32_t FRAME_RATE = 30;
const double speed = 10;

class Game
{
private:
	string name;

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	bool exit = false;
	int puntuacion;
	Texture* texturas_[NUM_TEXTURES];
	Texture* backgrounds_[4];
	Bow* bow_;
	vector<Arrow*> arrows_;
	vector<Balloon*> balloons_;
	ScoreBoard* score;

	list<GameObject*> gameObjects_;
	list<EventHandler*> eventHandlers_;

	SDL_Rect flechasRect;
	SDL_Rect puntRect;

	int arrowsLeft = 10;
	int level;

	struct TexturesAtributes {
		string nombre;
		int row;
		int col;
	};
	TexturesAtributes atributes_[NUM_TEXTURES] = { "Bow1.png", 1, 1, "Bow2.png", 1, 1, "Arrow1.png", 1, 1, "balloons.png", 7, 6, "bg1.png", 1, 1, "digits1.png", 1, 10, "butterfly.png", 4, 10};

	void generate();
	void nextLevel();

public:
	Game();
	~Game();
	void run();
	void render();
	void update();
	void handleEvents();
	void saveGame(string file);
};
	
	

