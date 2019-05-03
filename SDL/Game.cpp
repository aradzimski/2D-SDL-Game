#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Collision.h"
#include "Text.h"
#include <vector>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Player* player;
Text* deathCounterText;
Text* deathCounterText2;
Text* coinCounterText;
Text* coinCounterText2;
Map* map;
SDL_Rect Game::camera = { 0, 0, 12800, 12800};

bool checkpoint_collision;
bool gate_collision;
bool coin_collision;
bool enemy_collision;

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

		if (TTF_Init() == -1) {
			printf("TTF_Init: %s\n", TTF_GetError());
			exit(2);
		}

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

		renderer = SDL_CreateRenderer(window, 2, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		running = true;
	}

	else
	{
		running = false;
	}

	deathCounterText =  new Text("Assets/Fonts/font.ttf", 32, "Deaths: ", { 255,0,0,255 });
	deathCounterText2 = new Text("Assets/Fonts/font.ttf", 32, "0", { 255,0,0,255 });
	deathCounter = 0;

	coinCounterText = new Text("Assets/Fonts/font.ttf", 32, "Coins: ", { 255,255,0,255 });
	coinCounterText2 = new Text("Assets/Fonts/font.ttf", 32, "0", { 255,255,0,255 });
	coinCounter = 0;

	map = new Map("Assets/Maps/level1.map");

	// Pierwszy checkpoint
	checkpoint_x = map->getStartPosX();
	checkpoint_y = map->getStartPosY();
	
	for (auto& i : map->getEnemiesList())
	{
		i->setMapSize(map->getSizeX(), map->getSizeY());
		i->setCollidingTiles(map->getCollidingTiles());
	}

	player = new Player("Assets/Sprites/Player.png", map->getStartPosX(), map->getStartPosY());

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

	checkpoint_collision = false;
	for (auto& i : map->getCheckpointsList())
	{
		checkpoint_collision = Collision::checkCollision(i->getRect(), player->getRect());

		if (checkpoint_collision)
		{
			checkpoint_x = i->getCheckpointX();
			checkpoint_y = i->getCheckpointY();
		}
	}

	gate_collision = false;
	for (auto& i : map->getGatesList())
	{
		gate_collision = Collision::checkCollision(i->getRect(), player->getRect());

		if (gate_collision)
		{
			this->changeMap(map->getNextLevel().c_str());
		}
	}

	coin_collision = false;

	for (auto& i : map->getCoinsList())
	{
		if (i->isActive())
		{
			coin_collision = Collision::checkCollision(i->getRect(), player->getRect());

			if (coin_collision)
			{
				i->setActive(false);
				coinCounter++;
				delete coinCounterText2;
				delete deathCounterText2;
				coinCounterText2 = new Text("Assets/Fonts/font.ttf", 32, std::to_string(coinCounter), { 255,255,0,255 });
				deathCounterText2 = new Text("Assets/Fonts/font.ttf", 32, std::to_string(deathCounter), { 255,0,0,255 });
			}
		}
	}
	
	enemy_collision = false;
	for (auto& i : map->getEnemiesList())
	{
		i->Update();
		enemy_collision = Collision::checkEnemyCollision(i->getRect(), player->getRect());

		if (enemy_collision)
		{
			player->setPositionX(checkpoint_x); 
			player->setPositionY(checkpoint_y);
			deathCounter++;
			delete coinCounterText2;
			delete deathCounterText2;
			coinCounterText2 = new Text("Assets/Fonts/font.ttf", 32, std::to_string(coinCounter), { 255,255,0,255 });
			deathCounterText2 = new Text("Assets/Fonts/font.ttf", 32, std::to_string(deathCounter), { 255,0,0,255 });
		}
	}

	camera.x = player->getPositionX() - (1920 / 2);
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

	for (auto& i : map->getCheckpointsList())
	{
		i->Render();
	}

	for (auto& i : map->getGatesList())
	{
		i->Render();
	}

	for (auto& i : map->getCoinsList())
	{
		if (i->isActive())
		{
			i->Render();
		}
	}

	for (auto& i : map->getEnemiesList())
	{
		i->Render();
	}

	player->Render();

	deathCounterText->Render(20, 1080 - 50);
	deathCounterText2->Render(135, 1080 - 50);

	coinCounterText->Render(20, 1080 - 100);
	coinCounterText2->Render(115, 1080 - 100);
	SDL_RenderPresent(renderer);
};

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
}

void Game::changeMap(const char* path)
{
	map = new Map(path);

	// Pierwszy checkpoint
	checkpoint_x = map->getStartPosX();
	checkpoint_y = map->getStartPosY();

	for (auto& i : map->getEnemiesList())
	{
		i->setMapSize(map->getSizeX(), map->getSizeY());
		i->setCollidingTiles(map->getCollidingTiles());
	}

	player = new Player("Assets/Sprites/Player.png", map->getStartPosX(), map->getStartPosY());

	player->setMapSize(map->getSizeX(), map->getSizeY());
	player->setCollidingTiles(map->getCollidingTiles());
}