#pragma once
#include "Game.h"
#include "Velocity.h"
#include "Enemy.h"

class Collision
{

public:

	static bool checkCollision(SDL_Rect A, SDL_Rect B);
	static SDL_Rect calculateCollision(SDL_Rect A, SDL_Rect B, Velocity* velocity);
	static SDL_Rect calculateEnemyCollision(SDL_Rect A, SDL_Rect B, Velocity* velocity, Enemy* enemy);

private:

	Collision();

};
