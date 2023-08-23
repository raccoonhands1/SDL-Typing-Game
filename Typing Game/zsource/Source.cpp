#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Globals.h"
#include "Game.h"

using namespace std;

Game* game = nullptr;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
int WIDTH = 1280, HEIGHT = 720;
SDL_Color Black = { 0, 0, 0 };
SDL_Color White = { 200, 200, 200 };


int main(int argc, char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("Typing Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

	while (game->running()) {



		frameStart = SDL_GetTicks();


		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->clean();


	return 0;
}
