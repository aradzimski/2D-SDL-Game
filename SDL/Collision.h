#pragma once
#include "Game.h"
#include "Velocity.h"

class Collision
{

public:

	static bool checkCollision(SDL_Rect A, SDL_Rect B);
	static SDL_Rect calculateCollision(SDL_Rect A, SDL_Rect B, Velocity* velocity);

private:

	Collision();

};
