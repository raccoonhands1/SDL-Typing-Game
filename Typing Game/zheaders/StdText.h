#pragma once
#include "GameObject.h"

class StdText : public GameObject
{
public:
	~StdText();
	StdText();
	StdText(SDL_Renderer* ren, const char* text, const char* font);

	void Render() override;
	void Update() override;
	void Highlight(SDL_Color colorStruct);
	void Reset();

	char getCurrentChar() { std::cout << _text[_current] << std::endl; return toupper(_text[_current]); }
	const char* getText() { return _text; }
	int getScaleFactor() { return _scaleFactor; }
	int getCurrent() { return _current; }
	TTF_Font* getFont() { return _font; }
	SDL_Color getColor() { return _color; }
	SDL_Rect getRect(int current) { return renderQuad[current]; }

	//these are for the indicator class
	int getXPosOfArrayOfChar(int current) { return _xposArr[current]; }

	void setText(const char* text) { _text = text; }
	void currentPlusOne() { _current++; }

protected:
	TTF_Font* _font;
	SDL_Color _color;
	SDL_Rect tDestRect;
	SDL_Surface* surfaceMessage;
	SDL_Rect renderQuad[100];
	
	int _xposArr[100];
	int _scaleFactor = 10;
	int _current;
	const char* _text;
	SDL_Color _colorA[100]; // this is an array of size 15 which specifies the colour of each character.

};

class Indicator : public StdText
{
public:
	~Indicator();
	Indicator(SDL_Renderer* ren);
	//init render on the first character
	void Render(StdText* text);

};