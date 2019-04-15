#include "Map.h"
#include <string>

Map::Map()
{
	// wczytujemy poziom razem z tilesetem z pliku mapy

	doc.LoadFile("Assets/Maps/level1.xml");
	
	// Rozmiar mapy
	size_x = doc
		.FirstChildElement("map")
		->IntAttribute("width");
	size_y = doc
		.FirstChildElement("map")
		->IntAttribute("height");

	// Tileset
	std::string tilesetname = (char*)doc
		.FirstChildElement("map")
		->FirstChildElement("tileset")
		->Attribute("source");

	tileset = new Tileset(tilesetname);

	// Budowanie mapy

	src.x = src.y = 0;
	src.w = dest.w = Tileset::TILE_SIZE;
	src.h = dest.h = Tileset::TILE_SIZE;
	dest.x = dest.y = 0;
}

void Map::DrawMap()
{
	//parsujemy

	/*int type = 0;
	for (int row = 0; row < size_y; row++)
	{
		for (int column = 0; column < size_x; column++)
		{
			type = level[row][column];

			

			dest.x = column * Tileset::TILE_SIZE;
			dest.y = row * Tileset::TILE_SIZE;

			SDL_Rect drawingRect = { dest.x - Game::camera.x, dest.y - Game::camera.y, dest.w, dest.h };

			tileset->vTiles[type].DrawTile(src, drawingRect);
		}
	}*/
}
