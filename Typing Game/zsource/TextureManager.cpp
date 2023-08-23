#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* ren, const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

