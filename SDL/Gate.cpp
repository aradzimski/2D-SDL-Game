#include "Gate.h"

Gate::Gate(const char* sprite, int xpos, int ypos)
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
}

int Gate::getGateX()
{
	return xpos;
}

int Gate::getGateY()
{
	return ypos;
}

SDL_Rect Gate::getRect()
{
	return destRect;
}

void Gate::Render()
{
	drawingRect = { destRect.x - Game::camera.x, destRect.y - Game::camera.y, destRect.w, destRect.h };
	SDL_RenderCopy(Game::renderer, oTexture, &srcRect, &drawingRect);
}