#pragma once

#include "Velocity.h"
#include "TextureManager.h"
#include "Tile.h"
#include <vector>

class Enemy {

public:
	Enemy(const char* texturesheet, int x, int y, bool movUp, bool movDown, bool movLeft, bool movRight, int speed);
	~Enemy();

	void Update();
	void Render();

	int getPositionX();
	int getPositionY();
	void setPositionX(int xpos);
	void setPositionY(int ypos);

	void setMapSize(int size_x, int size_y);
	void setCollidingTiles(std::vector<class Tile*> tiles);

	bool movUp;
	bool movDown;
	bool movLeft;
	bool movRight;

	SDL_Rect getRect();

private:
	int oSize;
	int xpos;
	int ypos;

	// kolizja
	int map_size_x;
	int map_size_y;
	std::vector<class Tile*> CollidingTiles;

	int velocityFactorX;
	int velocityFactorY;

	Velocity* oVelocity;
	SDL_Texture* oTexture;
	SDL_Rect srcRect, destRect, drawingRect;

	void setVelocityFactor();
};