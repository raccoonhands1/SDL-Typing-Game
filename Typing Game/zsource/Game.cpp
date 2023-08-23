#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "StdText.h"
#include <vector>
#include <inttypes.h>
#include "Indicator.h"
#include <fstream>
#include <sstream>

GameObject* player; // remove if necessary
StdText* text;
Indicator* ind;

const char* OpenSans = "assets/fonts/OpenSans.ttf";
uint8_t WPM = 0;

std::vector<std::string> wordVector;

Game::Game() { }

Game::~Game() { }

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0) {
		std::cout << "SDL && ttf Initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Created Window" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 22, 28, 36, 255);
			std::cout << "Renderer Created" << std::endl;
		}
		isRunning = true;
	}

	//init game objects
	player = new GameObject(renderer, "assets/player.png"); // this is just for display
	text = new StdText(renderer, "HELLO WORLD", OpenSans);
	ind = new Indicator(renderer);

	//init words vector
	int count = 0;
	std::ifstream intext("Samples.txt"); //read from file
	while (count < 1000) {
		std::string line = "";
		std::getline(intext, line);
		wordVector.push_back(line);
		count++;
	}
	intext.close();
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN: // keypress event
		if (*SDL_GetKeyName(event.key.keysym.sym) == text->getCurrentChar() || strcmp(SDL_GetKeyName(event.key.keysym.sym), "Space") == 0 && text->getCurrentChar() == *" ") {
			text->Highlight({ 50, 190, 53, 255 });
			text->currentPlusOne();
		} else {
			text->Highlight({ 200, 25, 25, 200 });
		}
		if (text->getCurrentChar() == '\0') { // finish word
			std::cout << "WORDS FINISHED" << std::endl;

			text->setText(wordVector.at(rand() % 1000).c_str()); //sets the text to a random word in the word vector
			text->Reset();
		}
		break;
	default:
		break;
	}


}

void Game::update() {
	count++;

	text->Update();

	std::cout << count << std::endl;
}

void Game::render() {
	SDL_RenderClear(renderer);

	//player->Render();
	ind->Render(text);
	text->Render();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);

	SDL_DestroyRenderer(renderer);

	SDL_Quit();
}