#include "Sprite.h"

Sprite::Sprite(SDL_Texture* sTexture, int stID)
{
	this->sTexture = sTexture;
	this->sID = sID;
}

Sprite::~Sprite()
{
}

int Sprite::getID()
{
	return sID;
}

SDL_Texture* Sprite::getTexture()
{
	return sTexture;
}
