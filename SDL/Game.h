#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Game
{

public:
	Game();
	~Game();

	void initialize(const char* title, float pos_x, float pos_y, int width, int height, int fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool isRunning() { return running; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;

	void changeMap(const char* path);

private:

	SDL_Window *window;

	bool running;
	int cnt = 0;
	
	int deathCounter = 0;
	int checkpoint_x = 0;
	int checkpoint_y = 0;

};

