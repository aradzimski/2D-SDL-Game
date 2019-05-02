#pragma once

#include "TextureManager.h"
#include "Animation.h"

class Checkpoint {

public:
	Checkpoint(const char* sprite, int xpos, int ypos, bool animated);
	Checkpoint(const char* sprite, int xpos, int ypos, bool animated, Animation* animation);
	~Checkpoint();

	int getCheckpointX();
	int getCheckpointY();
	SDL_Rect getRect();

	void Render();

private:

	int xpos;
	int ypos;
	bool animated;
	Animation* animation;

	SDL_Rect srcRect, destRect;
	SDL_Texture* oTexture;
};
