#pragma once 
#include "Tileset.h"
#include "TextureManager.h"

class Map 
{
public:

	Map();
	~Map();

	void LoadMap(int arr[128][128]);
	void DrawMap();

private:

	SDL_Rect src, dest, drawingRect;
	SDL_Texture* water;
	SDL_Texture* ground;
	Tileset* tileset;

	int map[128][128];

};