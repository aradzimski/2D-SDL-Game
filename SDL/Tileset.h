#pragma once
#include <vector>
#include "Tile.h"

class Tileset {

public:

	Tileset(const char* spritesheet);
	~Tileset();

	static int TILE_SIZE;
	std::vector<class Tile> vTiles;

private:

	int spritesheetRows;
	int spritesheetColumns;
	SDL_Texture* tilesetTexture;
	SDL_Surface* tempSurface;
	SDL_Surface* tempTileSurface;
	SDL_Texture* tileTexture;

	int cropX;
	int cropY;

	int tileID;

};