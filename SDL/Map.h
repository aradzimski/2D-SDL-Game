#pragma once 
#include "Tileset.h"
#include "TextureManager.h"
#include "Animation.h"
#include "tinyxml2.h"
#include "Tile.h"
#include <vector>

class Map 
{
public:
	Map(const char* path);
	~Map();
	void DrawMap();
	std::vector<class Tile*> getCollidingTiles();
	int getSizeX();
	int getSizeY();

private:

	SDL_Rect src, dest, drawingRect;
	Tileset* tileset;
	tinyxml2::XMLDocument doc;
	std::vector<std::vector<int> > map;
	std::vector<class Tile*> Tiles;
	int tiles_size;
	std::vector<class Tile*> CollidingTiles;

	bool ignoreFurtherCommands;

	Animation* anim = nullptr;
	int tileID;
	bool animation;
	bool collision;
	int animationDelay;

	int size_x;
	int size_y;

};