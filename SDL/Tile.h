#pragma once
#include "TextureManager.h"

class Tile {

public:

	Tile(SDL_Texture* tTexture, int tID);
	~Tile();

	void DrawTile(SDL_Rect srcRect, SDL_Rect destRect);

private:

	SDL_Texture* tTexture;
	
	int tID;

	bool collision;

};