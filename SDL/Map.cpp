#include "Map.h"
#include "Tile.h"
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

	map = std::vector<std::vector<int> >(size_y, std::vector<int>(size_x, 0));
	
	char* layer;
	tinyxml2::XMLElement* layerElement = doc.FirstChildElement("map")->FirstChildElement("layer");
	for (int y = 0; y < size_y; y++)
	{
		layer = (char*)layerElement->GetText();
		for (int x = 0; x < size_x; x++)
		{
			map[y][x] = layer[x] - 48; // konwersja char na int
		}
		layerElement = layerElement->NextSiblingElement("layer");
	}

	int type = 0;
	for (int column = 0; column < size_x; column++)
	{
		for (int row = 0; row < size_y; row++)
		{
			type = map[column][row];

			if (type == 2)
			{
				Animation* aWater = new Animation(tileset, 60);
				aWater->addTile(2); 
				aWater->addTile(3);
				Tile* tile = new Tile(tileset, type, row, column, true, aWater, true);
				Tiles.push_back(tile);
			}
			else
			{
				Tile* tile = new Tile(tileset, type, row, column);
				Tiles.push_back(tile);
			}
		}
	}
}

void Map::DrawMap()
{
	for (int i = 0; i < Tiles.size(); i++)
	{
		Tiles[i]->update();
	}
	
}
