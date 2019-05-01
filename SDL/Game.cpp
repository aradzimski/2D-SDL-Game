#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include <vector>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Player* player;
std::vector<class Enemy*> Enemies;
Map* map;
SDL_Rect Game::camera = { 0, 0, 12800, 12800};

Game::Game()
{
}


Game::~Game()
{
}

void Game::initialize(const char* title, float pos_x, float pos_y, int width, int height, int fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{

		int flags = 0;
		if (fullscreen == 1)
		{
			flags = SDL_WINDOW_BORDERLESS; // do sprawdzenia póŸniej - borderless fullscreen
		}
		else if (fullscreen == 2)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(
			title,
			pos_x, pos_y,
			width, height,
			flags
		);

		renderer = SDL_CreateRenderer(window, 2, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		running = true;
	}

	else
	{
		running = false;
	}
	
	player = new Player("Assets/Sprites/Player.png", 500, 500);

	Enemies.push_back(new Enemy("Assets/Sprites/Enemy.png", 700, 350, true, false, true, false));
	Enemies.push_back(new Enemy("Assets/Sprites/Enemy.png", 200, 250, false, false, false, false));

	map = new Map("Assets/Maps/level1.map");
	
	for (auto& i : Enemies)
	{
		i->setMapSize(map->getSizeX(), map->getSizeY());
		i->setCollidingTiles(map->getCollidingTiles());
	}

	player->setMapSize(map->getSizeX(), map->getSizeY());
	player->setCollidingTiles(map->getCollidingTiles());
};

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	default:
		break;
	}
	if (Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_ESCAPE) {
		running = false;
	}
};

void Game::update()
{
	player->Update();

	bool collision = false;
	for (auto& i : Enemies)
	{
		i->Update();
		collision = Collision::checkCollision(i->getRect(), player->getRect());

		if (collision)
		{
			std::cout << "kolizja z enemy" << std::endl;
		}
	}

	camera.x = player->getPositionX() - (1920 / 2); // póŸniej pobraæ rozdzielczoœæ z pliku konfiguracyjnego
	camera.y = player->getPositionY() - (1080 / 2);


	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
};

void Game::render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();

	for (auto& i : Enemies)
	{
		i->Render();
	}

	player->Render();
	
	SDL_RenderPresent(renderer);
};

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
};