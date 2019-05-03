#pragma once

#include "TextureManager.h"

class Gate{

public:
	Gate(const char* sprite, int xpos, int ypos);
	~Gate();

	int getGateX();
	int getGateY();
	SDL_Rect getRect();

	void Render();

private:

	int xpos;
	int ypos;

	SDL_Rect srcRect, destRect, drawingRect;
	SDL_Texture* oTexture;
};
