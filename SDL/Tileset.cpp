#include "Tileset.h"

int Tileset::TILE_SIZE = 64;

Tileset::Tileset(std::string spritesheet)
{
	// Domyœlny folder z tilesetami
	spritesheet = "Assets/Tilesets/" + spritesheet;
	SDL_Surface* tempSurface = IMG_Load(spritesheet.c_str());

	spritesheetRows = tempSurface->h / TILE_SIZE;
	spritesheetColumns = tempSurface->w / TILE_SIZE;

	cropX = 0;
	cropY = 0;
	tileID = 0;

	// Dla ka¿dego bloku (domyœlnie 64x64) w importowanym obrazku tworzymy nowy obiekt Tile i przypisujemy mu teksturê.

	for (int row = 1; row <= spritesheetRows; row++)
	{
		cropX= 0;
		for (int col = 1; col <= spritesheetColumns; col++)
		{
			tempTileSurface = TextureManager::CropSurface(tempSurface, cropX, cropY);
			tileTexture = TextureManager::LoadTileTexture(tempTileSurface);
			Sprite tmpSprite(tileTexture, tileID);
			Sprites.push_back ( tmpSprite );
			cropX += TILE_SIZE;
			tileID++;
		}
		cropY += TILE_SIZE;
	}
	SDL_FreeSurface(tempTileSurface);
	SDL_DestroyTexture(tileTexture);
}

Tileset::~Tileset()
{
	SDL_FreeSurface(tempTileSurface);
	SDL_DestroyTexture(tileTexture);
}
