#pragma once
#include "Game.h"
#include "Tileset.h"

class TextureManager {

public:

	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
	static SDL_Surface* CropSurface(SDL_Surface* spritesheet, int x, int y);
	static SDL_Texture* LoadTileTexture(SDL_Surface* surface);
};