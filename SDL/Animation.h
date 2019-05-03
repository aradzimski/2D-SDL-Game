#pragma once
#include <vector>
#include <string>
#include "TextureManager.h"
#include "Tileset.h"

class Animation {

public:
	Animation(Tileset* tileset, int delay);
	Animation(int delay);
	~Animation();

	void addTile(int tileID);
	void addSprite(SDL_Texture* sprite);
	int getTile(int tileID);
	int getTileQuantity();
	SDL_Texture* getNextTile();
	SDL_Texture* getNextSprite();
	
private:

	std::vector <int> AnimationTiles;
	std::vector <class SDL_Texture*> AnimationSprites;
	Tileset* tileset;
	SDL_Texture* nextTile;
	SDL_Texture* nextSprite;

	int delay = 1;
	int delay_counter;
	int tile_counter;
	int sprite_counter;
};
