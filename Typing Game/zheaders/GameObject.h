#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject(SDL_Renderer* ren, const char* texturesheet);
	GameObject();
	~GameObject();

	int getXPos() { return xpos; }

	virtual void Update();
	virtual void Render();

protected:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};

