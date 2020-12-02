#include <SDL.h>
#include "Game.h"
#include <iostream>
#include <thread>

Game *game = nullptr;

int main(int argc, char *argv[])
{

	const int FPS = 60;
	const float frameDelay = 1000.0f / FPS;

	Uint64 frameStart;
	float frameTime;

	game = new Game();

	game->initialize("2D SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 2);
	SDL_ShowCursor(0); // ukrywamy kursor

	while (game->isRunning()) 
	{
		frameStart = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	SDL_ShowCursor(1);
	game->clean();

	return EXIT_SUCCESS;
}