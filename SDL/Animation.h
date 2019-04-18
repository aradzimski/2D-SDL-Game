#pragma once
#include <vector>
#include "TextureManager.h"
#include "Tileset.h"

class Animation {

public:
	Animation(Tileset* tileset, int delay);
	~Animation();

	void addTile(int tileID);
	int getTile(int tileID);
	int getTileQuantity();
	SDL_Texture* getNextTile();
	
private:

	std::vector <int> AnimationTiles;
	Tileset* tileset;
	SDL_Texture* nextTile;

	int delay;
	int delay_counter;
	int tile_counter;
};
