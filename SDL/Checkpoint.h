#pragma once

#include "TextureManager.h"

class Checkpoint {

public:
	Checkpoint(const char* sprite, int xpos, int ypos);
	~Checkpoint();

	int getCheckpointX();
	int getCheckpointY();
	SDL_Rect getRect();

	void Render();

private:

	int xpos;
	int ypos;

	SDL_Rect srcRect, destRect;
	SDL_Texture* oTexture;
};
