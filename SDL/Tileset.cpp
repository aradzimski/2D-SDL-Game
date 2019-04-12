#include "Tileset.h"

int Tileset::TILE_SIZE = 64;

Tileset::Tileset(const char* spritesheet)
{
	// Dla ka¿dego bloku 64x64 w importowanym obrazku tworzymy nowy obiekt Tile i przypisujemy mu teksturê.

	SDL_Surface* tempSurface = IMG_Load(spritesheet);

	spritesheetRows = tempSurface->h / TILE_SIZE;
	spritesheetColumns = tempSurface->w / TILE_SIZE;

	cropX = 0;
	cropY = 0;
	tileID = 0;

	for (int col = 1; col <= spritesheetColumns; col++)
	{
		cropY = 0;
		for (int row = 1; row <= spritesheetRows; row++)
		{
			tempTileSurface = TextureManager::CropSurface(tempSurface, cropX, cropY);
			tileTexture = TextureManager::LoadTileTexture(tempTileSurface);
			Tile tmpTile(tileTexture, tileID);
			vTiles.push_back ( tmpTile );
			cropY += TILE_SIZE;
			tileID++;
		}
		cropX += TILE_SIZE;
	}
}

Tileset::~Tileset()
{
}
