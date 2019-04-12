#include "Tile.h"

Tile::Tile(SDL_Texture* tTexture, int tID)
{
	this->tTexture = tTexture;
	this->tID = tID;
	collision = false;
}

Tile::~Tile()
{
}

void Tile::DrawTile(SDL_Rect srcRect, SDL_Rect destRect)
{
	TextureManager::Draw(tTexture, srcRect, destRect);
}
