#pragma once 
#include "Tileset.h"
#include "TextureManager.h"
#include "Animation.h"
#include "tinyxml2.h"
#include "Tile.h"
#include "Enemy.h"
#include "Checkpoint.h"
#include "Gate.h"
#include "Coin.h"

class Map 
{
public:
	Map(const char* path);
	~Map();
	void DrawMap();
	std::vector<class Tile*> getCollidingTiles();
	int getSizeX();
	int getSizeY();

	std::vector<class Enemy*> getEnemiesList();
	std::vector<class Checkpoint*> getCheckpointsList();
	std::vector<class Gate*> getGatesList();
	std::vector<class Coin*> getCoinsList();

	int getStartPosX();
	int getStartPosY();

	bool checkLastMap();

	std::string getNextLevel();

private:

	int startposx;
	int startposy;

	bool lastmap;

	std::string nextlevel;

	SDL_Rect src, dest, drawingRect;
	Tileset* tileset;
	SDL_Texture* tmpTexture;
	tinyxml2::XMLDocument doc;
	std::vector<std::vector<int> > map;
	std::vector<class Tile*> Tiles;
	std::vector<class Tile*> CollidingTiles;

	std::vector<class Enemy*> Enemies;
	std::vector<class Checkpoint*> Checkpoints;
	std::vector<class Gate*> Gates;
	std::vector<class Coin*> Coins;

	bool ignoreFurtherCommands;

	Animation* anim = nullptr;
	int tileID;
	bool animation;
	bool collision;
	int animationDelay;

	int size_x;
	int size_y;

};