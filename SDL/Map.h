#pragma once 
#include "Tileset.h"
#include "TextureManager.h"
#include "tinyxml2.h"
#include <vector>

class Map 
{
public:
	Map();
	~Map();
	void DrawMap();

private:

	SDL_Rect src, dest, drawingRect;
	Tileset* tileset;
	tinyxml2::XMLDocument doc;

	int map;
	int size_x;
	int size_y;

};