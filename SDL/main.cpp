#include <SDL.h>
#include "Game.h"
#include <iostream>

Game *game = nullptr;

int main(int argc, char *argv[])
{

	const int FPS = 60;
	const float frameDelay = 1000.0f / FPS;

	Uint64 frameStart;
	float frameTime;SDL

	game = new Game();

	game->initialize("Smieszna gierka", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 0);

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

	game->clean();

	return EXIT_SUCCESS;
}