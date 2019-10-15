#pragma once

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "Texture.h"
#include "Bow.h"
#include "Balloon.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const enum TexturesName{LBow, NLBow, Arrows, Ballons, Background, Numbers};
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int NUM_TEXTURES = 6;
const string RUTA = "..\\images\\";
const uint32_t FRAME_RATE = 5;
const double speed = 10;

class Game
{
protected:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	bool exit = false;
	int puntuacion;
	Texture* texturas_[NUM_TEXTURES];
	Bow* bow_;
	vector<Arrow*> arrows_;
	vector<Balloon*> balloons_;

	struct TexturesAtributes {
		string nombre;
		int row;
		int col;
	};
	TexturesAtributes atributes_[NUM_TEXTURES] = { "Bow1.png", 1, 1, "Bow2.png", 1, 1, "Arrow1.png", 1, 1, "balloons.png", 7, 6, "bg1.png", 1, 1, "digits1.png", 1, 10 };

	void generate();

public:
	Game();
	~Game();
	void run();
	void render() const;
	void update();
	void handleEvents();
};
	
	

