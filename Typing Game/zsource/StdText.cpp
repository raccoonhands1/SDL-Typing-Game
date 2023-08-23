#include "StdText.h"
#include "Globals.h"
#include <fstream>
#include <sstream>


StdText::~StdText() {}
StdText::StdText() {
}

StdText::StdText(SDL_Renderer* ren, const char* text, const char* font) {
	renderer = ren;
	_font = TTF_OpenFont(font, 500);
	_text = text;
	_color = { 200, 200, 200, 255 };
	_colorA[strlen(_text)];
	_current = 0;

	for (int i = 0; i < strlen(_text); i++) { // set all colors in _colorA[] to be black
		_colorA[i] = _color;
	}
}

void StdText::Reset() {
	_color = { 200, 200, 200, 255 };
	_colorA[strlen(_text)];
	_current = 0;

	for (int i = 0; i < strlen(_text); i++) { // set all colors in _colorA[] to be black
		_colorA[i] = _color;
	}
}

void StdText::Update() {
	SDL_Surface* centerMessageW = TTF_RenderText_Solid(_font, _text, _color); //new surface to center the text

	xpos = (WIDTH / 2) - (centerMessageW->w / 2 / _scaleFactor); // starting x position

	SDL_FreeSurface(centerMessageW);
}

void StdText::Highlight(SDL_Color colorStruct) {
	_colorA[_current] = colorStruct;
}

void StdText::Render() { // Render() renders StdText input 1 character at a time. This is essential for highlighting to be possible.
	for (int i = 0; i < strlen(_text); i++) {
		std::string charAsString(1, _text[i]); // convert the const char* to a string to pass only one character. 

		surfaceMessage = TTF_RenderText_Solid(_font, charAsString.c_str(), _colorA[i]);
		
		renderQuad[i] = {xpos, (HEIGHT / 2) - (surfaceMessage->h / 2 / _scaleFactor), (surfaceMessage->w) / _scaleFactor, (surfaceMessage->h) / _scaleFactor};

		xpos += surfaceMessage->w / _scaleFactor;

		_xposArr[i] = xpos;

		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		
		SDL_RenderCopy(renderer, Message, nullptr, &renderQuad[i]);

		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
	}
}




Indicator::~Indicator() {}
Indicator::Indicator(SDL_Renderer* ren) {
	renderer = ren;
	xpos = 10;
	ypos = 10;

}


void Indicator::Render(StdText* text) {
	SDL_Rect renderQuad;

	renderQuad = { text->getXPosOfArrayOfChar(text->getCurrent()) - text->getRect(text->getCurrent()).w, (HEIGHT / 2) - 25, text->getRect(text->getCurrent()).w, 50 };

	SDL_SetRenderDrawColor(renderer, 0, 10, 35, 100);
	SDL_RenderFillRect(renderer, &renderQuad);
	SDL_SetRenderDrawColor(renderer, 22, 28, 36, 255);
}