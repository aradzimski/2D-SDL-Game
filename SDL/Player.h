#pragma once
#include "Velocity.h"
#include "TextureManager.h"

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

private:
	int oSize;
	float xpos;
	float ypos;

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