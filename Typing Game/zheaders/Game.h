#pragma once

#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Globals.h"

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	inline bool running() { return isRunning; }
private:
	int count;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

};