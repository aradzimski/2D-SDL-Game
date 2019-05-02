#pragma once 
#include "Tileset.h"
#include "TextureManager.h"
#include "Animation.h"
#include "tinyxml2.h"
#include "Tile.h"
#include "Enemy.h"
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

	std::vector<class Enemy*> getEnemiesList();

private:

	SDL_Rect src, dest, drawingRect;
	Tileset* tileset;
	tinyxml2::XMLDocument doc;
	std::vector<std::vector<int> > map;
	std::vector<class Tile*> Tiles;
	std::vector<class Tile*> CollidingTiles;

	std::vector<class Enemy*> Enemies;

	bool ignoreFurtherCommands;

	Animation* anim = nullptr;
	int tileID;
	bool animation;
	bool collision;
	int animationDelay;

	int size_x;
	int size_y;

};