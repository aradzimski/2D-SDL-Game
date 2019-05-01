#pragma once

#include "Velocity.h"
#include "TextureManager.h"
#include "Tile.h"
#include <vector>

class Enemy {

public:
	Enemy(const char* texturesheet, float x, float y, bool movUp, bool movDown, bool movLeft, bool movRight);
	~Enemy();

	void Update();
	void Render();

	float getPositionX();
	float getPositionY();
	void setPositionX(float xpos);
	void setPositionY(float ypos);

	void setMapSize(int size_x, int size_y);
	void setCollidingTiles(std::vector<class Tile*> tiles);

	bool movUp;
	bool movDown;
	bool movLeft;
	bool movRight;

	SDL_Rect getRect();

private:
	int oSize;
	float xpos;
	float ypos;

	// kolizja
	int map_size_x;
	int map_size_y;
	std::vector<class Tile*> CollidingTiles;

	float velocityFactorX;
	float velocityFactorY;

	Velocity* oVelocity;
	SDL_Texture* oTexture;
	SDL_Rect srcRect, destRect, drawingRect;

	void setVelocityFactor();
};