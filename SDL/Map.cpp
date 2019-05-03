#include "Map.h"
#include <string>

Map::Map(const char* path)
{
	// wczytujemy poziom razem z tilesetem z pliku mapy
	doc.LoadFile(path);
	
	// Rozmiar mapy
	size_x = doc
		.FirstChildElement("map")
		->IntAttribute("width");
	size_y = doc
		.FirstChildElement("map")
		->IntAttribute("height");

	// Pozycja startowa gracza
	startposx = doc
		.FirstChildElement("map")
		->IntAttribute("startposx");
	startposy = doc
		.FirstChildElement("map")
		->IntAttribute("startposy");

	// Nastêpna mapa
	nextlevel = doc
		.FirstChildElement("map")
		->Attribute("nextlevel");

	// Tileset
	std::string tilesetname = (char*)doc
		.FirstChildElement("map")
		->FirstChildElement("tileset")
		->Attribute("source");

	tileset = new Tileset(tilesetname);

	// Lista przeciwników

	std::string en_type;
	bool en_animation;
	std::string en_sprite;
	int en_xpos;
	int en_ypos;
	int en_speed;
	bool en_movUp;
	bool en_movDown;
	bool en_movLeft;
	bool en_movRight;

	for (tinyxml2::XMLElement* child = doc.FirstChildElement("map")->FirstChildElement("enemies")->FirstChildElement("enemy"); child; child = child->NextSiblingElement("enemy"))
	{
		en_type = child->Attribute("type");
		en_animation = child->BoolAttribute("animation");
		en_sprite = child->Attribute("sprite");
		en_xpos = child->IntAttribute("xpos");
		en_ypos = child->IntAttribute("ypos");
		en_speed = child->IntAttribute("speed");
		en_movUp = child->BoolAttribute("up");
		en_movDown = child->BoolAttribute("down");
		en_movLeft = child->BoolAttribute("left");
		en_movRight = child->BoolAttribute("right");

		std::string en_sprite_location = "Assets/Sprites/Enemies/" + en_type + "/";

		if (en_animation)
		{
			int en_animationDelay = child->IntAttribute("delay");
			Animation* en_anim = new Animation(en_animationDelay);

			for (tinyxml2::XMLElement* spriteAnimation = child->FirstChildElement("animation"); spriteAnimation; spriteAnimation = spriteAnimation->NextSiblingElement("animation"))
			{
				std::string spritename = spriteAnimation->Attribute("sprite");
				std::string spritepath = "Assets/Sprites/Enemies/" + en_type + "/" + spritename;
				tmpTexture = TextureManager::LoadTexture(spritepath.c_str());
				en_anim->addSprite(tmpTexture);
			}
			Enemies.push_back(
				new Enemy(
				(en_sprite_location + en_sprite).c_str(),
					en_xpos,
					en_ypos,
					en_movUp,
					en_movDown,
					en_movRight,
					en_movLeft,
					en_speed,
					en_animation,
					en_anim
				)
			);
		}
		else
		{
			Enemies.push_back(
				new Enemy(
				(en_sprite_location + en_sprite).c_str(), 
					en_xpos,
					en_ypos, 
					en_movUp, 
					en_movDown, 
					en_movRight, 
					en_movLeft, 
					en_speed,
					en_animation
				)
			);
		}
	}

	// Lista checkpointów

	std::string chkp_sprite;
	int chkp_xpos;
	int chkp_ypos;
	bool chkp_animation;

	for (tinyxml2::XMLElement* child = doc.FirstChildElement("map")->FirstChildElement("checkpoints")->FirstChildElement("checkpoint"); child; child = child->NextSiblingElement("checkpoint"))
	{
		chkp_sprite = child->Attribute("sprite");
		chkp_xpos = child->IntAttribute("xpos");
		chkp_ypos = child->IntAttribute("ypos");
		chkp_animation = child->BoolAttribute("animation");
		
		if (chkp_animation)
		{
			int chkp_delay = child->IntAttribute("delay");
			Animation* chkp_anim = new Animation(chkp_delay);

			for (tinyxml2::XMLElement* spriteAnimation = child->FirstChildElement("animation"); spriteAnimation; spriteAnimation = spriteAnimation->NextSiblingElement("animation"))
			{
				std::string spritename = spriteAnimation->Attribute("sprite");
				std::string spritepath = "Assets/Sprites/" + spritename;
				tmpTexture = TextureManager::LoadTexture(spritepath.c_str());
				chkp_anim->addSprite(tmpTexture);
			}
			Checkpoints.push_back(
				new Checkpoint(
				("Assets/Sprites/" + chkp_sprite).c_str(),
					chkp_xpos,
					chkp_ypos,
					chkp_animation,
					chkp_anim
				)
			);
		}
		else
		{
			Checkpoints.push_back(
				new Checkpoint(
				("Assets/Sprites/" + chkp_sprite).c_str(),
					chkp_xpos,
					chkp_ypos,
					chkp_animation
				)
			);
		}
	}

	// Lista wyjœæ z mapy

	std::string gate_sprite;
	int gate_xpos;
	int gate_ypos;

	for (tinyxml2::XMLElement* child = doc.FirstChildElement("map")->FirstChildElement("gates")->FirstChildElement("gate"); child; child = child->NextSiblingElement("gate"))
	{
		gate_sprite = child->Attribute("sprite");
		gate_xpos = child->IntAttribute("xpos");
		gate_ypos = child->IntAttribute("ypos");

		Gates.push_back(
			new Gate(
			("Assets/Sprites/" + gate_sprite).c_str(),
				gate_xpos,
				gate_ypos
			)
		);
	}

	// Lista pieni¹¿ków na mapie

	std::string coin_sprite;
	int coin_xpos;
	int coin_ypos;
	bool coin_animation;

	for (tinyxml2::XMLElement* child = doc.FirstChildElement("map")->FirstChildElement("coins")->FirstChildElement("coin"); child; child = child->NextSiblingElement("coin"))
	{
		coin_sprite = child->Attribute("sprite");
		coin_xpos = child->IntAttribute("xpos");
		coin_ypos = child->IntAttribute("ypos");
		coin_animation = child->BoolAttribute("animation");

		if (coin_animation)
		{
			int coin_delay = child->IntAttribute("delay");
			Animation* coin_anim = new Animation(coin_delay);

			for (tinyxml2::XMLElement* spriteAnimation = child->FirstChildElement("animation"); spriteAnimation; spriteAnimation = spriteAnimation->NextSiblingElement("animation"))
			{
				std::string spritename = spriteAnimation->Attribute("sprite");
				std::string spritepath = "Assets/Sprites/" + spritename;
				tmpTexture = TextureManager::LoadTexture(spritepath.c_str());
				coin_anim->addSprite(tmpTexture);
			}
			Coins.push_back(
				new Coin(
				("Assets/Sprites/" + coin_sprite).c_str(),
					coin_xpos,
					coin_ypos,
					coin_animation,
					coin_anim
				)
			);
		}
		else
		{
			Coins.push_back(
				new Coin(
				("Assets/Sprites/" + coin_sprite).c_str(),
					coin_xpos,
					coin_ypos,
					coin_animation
				)
			);
		}
	}

	// Budowanie mapy

	map = std::vector<std::vector<int> >(size_y, std::vector<int>(size_x, 0));
	
	int pointer = 0;
	bool commaseparator = false;
	char* layer;
	tinyxml2::XMLElement* layerElement = doc.FirstChildElement("map")->FirstChildElement("layer");
	for (int y = 0; y < size_y; y++)
	{
		layer = (char*)layerElement->GetText();
		pointer = 0;
		for (int x = 0; x < size_x; x++)
		{
			int value = 0;
			commaseparator = false;
			while (!commaseparator)
			{
				if (layer[pointer] == 44)
				{
					map[y][x] = value;
					commaseparator = true;
					pointer++;
				}
				else
				{
					value += layer[pointer] - 48; // konwersja char na int
					pointer++;
				}
			}
		}
		layerElement = layerElement->NextSiblingElement("layer");
	}

	int type = 0;
	for (int column = 0; column < size_y; column++)
	{
		for (int row = 0; row < size_x; row++)
		{
			ignoreFurtherCommands = false;
			type = map[column][row];

			// Pobieranie listy animacji i kolizji

			for (tinyxml2::XMLElement* child = doc.FirstChildElement("map")->FirstChildElement("specialtiles")->FirstChildElement("tile"); child; child = child->NextSiblingElement("tile"))
			{
				tileID = child->IntAttribute("id");
				animation = child->BoolAttribute("animation");
				collision = child->BoolAttribute("collision");

				if (animation)
				{
					animationDelay = child->IntAttribute("delay");
					anim = new Animation(tileset, animationDelay);

					for (tinyxml2::XMLElement* tileAnimation = child->FirstChildElement("animation"); tileAnimation; tileAnimation = tileAnimation->NextSiblingElement("animation"))
					{
						anim->addTile(tileAnimation->IntAttribute("tile"));
					}
				}
				if (type == tileID)
				{
					Tile* tile = new Tile(tileset, type, row, column, animation, anim, collision);
					if (collision)
					{
						CollidingTiles.push_back(tile);
					}
					Tiles.push_back(tile);
					ignoreFurtherCommands = true;
				}
			}
			if (true != ignoreFurtherCommands)
			{
				Tile* tile = new Tile(tileset, type, row, column);
				Tiles.push_back(tile);
			}
		}
	}
}

Map::~Map()
{
	SDL_DestroyTexture(tmpTexture);
}

void Map::DrawMap()
{
	for (auto& i : Tiles)
	{
		i->update();
	}
}

std::vector<class Tile*> Map::getCollidingTiles()
{
	return CollidingTiles;
}

int Map::getSizeX()
{
	return size_x;
}

int Map::getSizeY()
{
	return size_y;
}

std::vector<class Enemy*> Map::getEnemiesList()
{
	return Enemies;
}

std::vector<class Checkpoint*> Map::getCheckpointsList()
{
	return Checkpoints;
}

std::vector<class Gate*> Map::getGatesList()
{
	return Gates;
}

std::vector<class Coin*> Map::getCoinsList()
{
	return Coins;
}

int Map::getStartPosX()
{
	return startposx;
}

int Map::getStartPosY()
{
	return startposy;
}

std::string Map::getNextLevel()
{
	return "Assets/Maps/" + nextlevel;
}
