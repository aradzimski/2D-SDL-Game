#include "Animation.h"

Animation::Animation(Tileset* tileset, int delay)
{
	std::vector <int> AnimationTiles;

	this->tileset = tileset;
	this->delay = delay;

	delay_counter = 0;
	tile_counter = 0;
}

Animation::Animation(int delay)
{
    std::vector <std::string> AnimationSprites;

	this->delay = delay;

	delay_counter = 0;
	sprite_counter = 0;
}

void Animation::addTile(int tileID)
{
	AnimationTiles.push_back(tileID);
}

int Animation::getTile(int tileID)
{
	return AnimationTiles[tileID];
}

int Animation::getTileQuantity()
{
	return AnimationTiles.size();
}

SDL_Texture* Animation::getNextTile()
{
	if (delay_counter % (delay) == 0)
	{
		nextTile = tileset
			->Sprites[AnimationTiles[tile_counter]]
			.getTexture();

		tile_counter++;
	}

	delay_counter++;

	if (delay_counter == delay * 100000)
	{
		delay_counter = 0;
	}
	if (tile_counter == AnimationTiles.size())
	{
		tile_counter = 0;
	}
	return nextTile;
}

void Animation::addSprite(std::string path)
{
	AnimationSprites.push_back(path);
}

SDL_Texture* Animation::getNextSprite()
{
	if (delay_counter % (delay) == 0)
	{
		nextSprite = TextureManager::LoadTexture(AnimationSprites[sprite_counter].c_str());
		sprite_counter++;
	}

	delay_counter++;

	if (delay_counter == delay * 100000)
	{
		delay_counter = 0;
	}
	if (sprite_counter == AnimationSprites.size())
	{
		sprite_counter = 0;
	}
	return nextSprite;
}
