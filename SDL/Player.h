#pragma once
#include "Velocity.h"
#include "TextureManager.h"
#include "Tile.h"

class Player {

public:
	Player(const char* texturesheet, float x, float y);
	~Player();

	void Update();
	void Render();

	float getPositionX();
	float getPositionY();
	void setPositionX(float xpos);
	void setPositionY(float ypos);

	void setMapSize(int size_x, int size_y);
	void setCollidingTiles(std::vector<class Tile*> tiles);

private:
	int oSize;
	float xpos;
	float ypos;
	
	// kolizja
	int map_size_x;
	int map_size_y;
	std::vector<class Tile*> CollidingTiles;

	bool movUp;
	bool movDown;
	bool movLeft;
	bool movRight;

	float velocityFactorX;
	float velocityFactorY;

	Velocity* oVelocity;
	SDL_Texture* oTexture;
	SDL_Rect srcRect, destRect, drawingRect;

	void setVelocityFactor();
};