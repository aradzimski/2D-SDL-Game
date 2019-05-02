#pragma once

#include "TextureManager.h"
#include "Animation.h"

class Coin {

public:
	Coin(const char* sprite, int xpos, int ypos, bool animated);
	Coin(const char* sprite, int xpos, int ypos, bool animated, Animation* animation);
	~Coin();

	int getCoinX();
	int getCoinY();
	SDL_Rect getRect();

	void Render();
	bool isActive();
	void setActive(bool set);

private:

	int xpos;
	int ypos;
	bool active;
	bool animated;
	Animation* animation;

	SDL_Rect srcRect, destRect;
	SDL_Texture* oTexture;
};