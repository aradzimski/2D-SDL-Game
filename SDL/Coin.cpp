#include "Coin.h"

Coin::Coin(const char* sprite, int xpos, int ypos, bool animated)
{
	oTexture = TextureManager::LoadTexture(sprite);

	this->xpos = xpos;
	this->ypos = ypos;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = Tileset::TILE_SIZE;
	srcRect.h = Tileset::TILE_SIZE;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = Tileset::TILE_SIZE;
	destRect.h = Tileset::TILE_SIZE;

	active = true;
}

Coin::Coin(const char* sprite, int xpos, int ypos, bool animated, Animation* animation)
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

	active = true;
}

int Coin::getCoinX()
{
	return xpos;
}

int Coin::getCoinY()
{
	return ypos;
}

SDL_Rect Coin::getRect()
{
	return destRect;
}

bool Coin::isActive()
{
	return active;
}

void Coin::setActive(bool set)
{
	active = set;
}

void Coin::Render()
{
	SDL_Rect drawingRect = { destRect.x - Game::camera.x, destRect.y - Game::camera.y, destRect.w, destRect.h };

	if (animated)
	{
		oTexture = animation->getNextSprite();
	}

	SDL_RenderCopy(Game::renderer, oTexture, &srcRect, &drawingRect);
}