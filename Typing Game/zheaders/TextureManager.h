#pragma once
#include "Game.h"
class TextureManager
{
public:
	static SDL_Texture* LoadTexture(SDL_Renderer* ren, const char* fileName);
};

