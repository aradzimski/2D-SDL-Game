#pragma once
#include <vector>
#include "TextureManager.h"
#include "Tileset.h"

class Tile {
	
public:

	Tile(Tileset* tileset, int tiletype, int column, int row, bool collision = false, bool animation = false);
	~Tile();

	bool getAnimation();
	void setAnimation(bool animation);
	bool getCollision();
	void setCollision(bool collision);
	
	SDL_Rect getSourceRect();
	void setSourceRect(SDL_Rect srcRect);
	SDL_Rect getDestinationRect();
	void setDestinationRect(SDL_Rect destRect);

	void update();

private:

	bool animation;
	bool collision;

	int column;
	int row;

	SDL_Texture* texture;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	Tileset* tileset;
	std::vector <int> AnimationTiles;

};
