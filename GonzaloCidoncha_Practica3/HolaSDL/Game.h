#pragma once

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "checkML.h"
#include "Texture.h"
#include "Bow.h"
#include "Balloon.h"
#include "Butterfly.h"
#include "ScoreBoard.h"
#include "Reward.h"
#include "GameStateMachine.h"
#include "List.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

const enum TexturesName{LBow, NLBow, Arrows, Ballons, Background, Numbers, Butterflies, Rewards, Bubble, PlayB, ExitB, MenuB, ResumeB};
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int NUM_TEXTURES = 13;
const string RUTA = "..\\images\\";
const uint32_t FRAME_RATE = 30;
const double speed = 10;

class Game
{
public:

	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	bool exit = false;
	struct TexturesAtributes {
		string nombre;
		int row;
		int col;
	};
	TexturesAtributes atributes_[NUM_TEXTURES] = { "Bow1.png", 1, 1, "Bow2.png", 1, 1, "Arrow1.png", 1, 1, "balloons.png", 7, 6, "bg1.png", 1, 1, "digits1.png", 1, 10, "butterfly.png", 4, 10, "rewards.png", 10, 8  , "bubble.png", 1, 1  ,
													"buttonPlay.png", 1, 1,  "buttonExit.png", 1, 1,  "buttonMenu.png", 1, 1,  "buttonResume.png", 1, 1};
	Texture* texturas_[NUM_TEXTURES];
	Texture* backgrounds_[4];

	GameStateMachine* gsm;

	Game();
	~Game();

	SDL_Renderer* getRenderer() { return renderer_; }

	GameStateMachine* getGSM() { return gsm; }

	void run();
	void render();
	void update();
	void handleEvents();
	
};
	
	

