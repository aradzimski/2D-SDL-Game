#include "Checkpoint.h"

Checkpoint::Checkpoint(const char* sprite, int xpos, int ypos, bool animated)
{
	oTexture = TextureManager::LoadTexture(sprite);

	this->xpos = xpos;
	this->ypos = ypos;
	this->animated = animated;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = Tileset::TILE_SIZE;
	srcRect.h = Tileset::TILE_SIZE;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = Tileset::TILE_SIZE;
	destRect.h = Tileset::TILE_SIZE;
}

Checkpoint::Checkpoint(const char* sprite, int xpos, int ypos, bool animated, Animation* animation)
{
	oTexture = TextureManager::LoadTexture(sprite);

	this->xpos = xpos;
	this->ypos = ypos;
	this->animated = animated;
	this->animation = animation;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = Tileset::TILE_SIZE;
	srcRect.h = Tileset::TILE_SIZE;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = Tileset::TILE_SIZE;
	destRect.h = Tileset::TILE_SIZE;
}

int Checkpoint::getCheckpointX()
{
	return xpos;
}

int Checkpoint::getCheckpointY()
{
	return ypos;
}

SDL_Rect Checkpoint::getRect()
{
	return destRect;
}

void Checkpoint::Render()
{
	drawingRect = { destRect.x - Game::camera.x, destRect.y - Game::camera.y, destRect.w, destRect.h };

	if (animated)
	{
		oTexture = animation->getNextSprite();
	}

	SDL_RenderCopy(Game::renderer, oTexture, &srcRect, &drawingRect);
}
