#include "Tile.h"

Tile::Tile(Tileset* tileset, int tiletype, int column, int row, bool animation, Animation* a, bool collision)
{
	this->tileset = tileset;
	this->collision = collision;
	this->animation = animation;
	this->column = column;
	this->row = row; 
	this->tAnimation = a;

	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = Tileset::TILE_SIZE;
	srcRect.h = destRect.h = Tileset::TILE_SIZE;
	destRect.x = destRect.y = 0;

	texture = tileset->Sprites[tiletype].getTexture();
}

Tile::Tile(Tileset* tileset, int tiletype, int column, int row, bool collision)
{
	this->tileset = tileset;
	this->collision = collision;
	this->animation = false;
	this->column = column;
	this->row = row;

	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = Tileset::TILE_SIZE;
	srcRect.h = destRect.h = Tileset::TILE_SIZE;
	destRect.x = destRect.y = 0;

	texture = tileset->Sprites[tiletype].getTexture();

}

bool Tile::getAnimation()
{
	return animation;
}

void Tile::setAnimation(bool animation)
{
	this->animation = animation;
}

bool Tile::getCollision()
{
	return collision;
}

void Tile::setCollision(bool collision)
{
	this->collision = collision;
}

SDL_Rect Tile::getSourceRect()
{
	return srcRect;
}

void Tile::setSourceRect(SDL_Rect srcRect)
{
	this->srcRect = srcRect;
}

SDL_Rect Tile::getDestinationRect()
{
	return destRect;
}

void Tile::setDestinationRect(SDL_Rect destRect)
{
	this->destRect = destRect;
}

void Tile::update()
{
	destRect.x = column * Tileset::TILE_SIZE;
	destRect.y = row * Tileset::TILE_SIZE;

	SDL_Rect drawingRect = { destRect.x - Game::camera.x, destRect.y - Game::camera.y, destRect.w, destRect.h };

	if (animation)
	{
		texture = tAnimation->getNextTile();
	}

	TextureManager::Draw(texture, srcRect, drawingRect);
}
