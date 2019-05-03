#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) 
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) 
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

SDL_Surface* TextureManager::CropSurface(SDL_Surface* spritesheet, int x, int y)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(spritesheet->flags, Tileset::TILE_SIZE, Tileset::TILE_SIZE, spritesheet->format->BitsPerPixel, spritesheet->format->Rmask, spritesheet->format->Gmask, spritesheet->format->Bmask, spritesheet->format->Amask);

	SDL_Rect rect = { x, y, Tileset::TILE_SIZE, Tileset::TILE_SIZE };

	SDL_BlitSurface(spritesheet, &rect, surface, 0);

	return surface;
}

SDL_Texture* TextureManager::LoadTileTexture(SDL_Surface* surface)
{
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	return tex;
}
