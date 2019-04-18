#include "Animation.h"

Animation::Animation(Tileset* tileset, int delay)
{
	std::vector <int> AnimationTiles;

	this->tileset = tileset;
	this->delay = delay;

	delay_counter = 0;
	tile_counter = 0;
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
	delay_counter++;

	if (delay_counter % (delay) == 0)
	{
		nextTile = tileset
			->Sprites[AnimationTiles[tile_counter]]
			.getTexture();

		tile_counter++;
	}
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
