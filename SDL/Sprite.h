#pragma once
#include "TextureManager.h"

class Sprite {

public:

	Sprite(SDL_Texture* sTexture, int sID);
	~Sprite();

	int getID();
	SDL_Texture* getTexture();

private:

	int sID;
	SDL_Texture* sTexture;

};