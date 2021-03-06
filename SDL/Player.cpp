#include "Player.h"
#include "Collision.h"

Player::Player(int x, int y)
{
	animation = new Animation(4);

	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player.png");
	animation->addSprite(oTexture);
	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player_2.png");
	animation->addSprite(oTexture);
	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player_3.png");
	animation->addSprite(oTexture);
	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player_4.png");
	animation->addSprite(oTexture);
	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player_5.png");
	animation->addSprite(oTexture);
	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player_6.png");
	animation->addSprite(oTexture);
	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player_7.png");
	animation->addSprite(oTexture);
	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player_8.png");
	animation->addSprite(oTexture);
	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player_9.png");
	animation->addSprite(oTexture);
	oTexture = TextureManager::LoadTexture("Assets/Sprites/Player_10.png");
	animation->addSprite(oTexture);


	xpos = x;
	ypos = y;
	oSize = 64;

	movUp = false;
	movDown = false;
	movLeft = false;
	movRight = false;
	
	oVelocity = new Velocity(0.6f, 0.91f, 7);
}

Player::~Player()
{
}

void Player::Update()
{
	oTexture = animation->getNextSprite();

	if (Game::event.type == SDL_KEYDOWN)
	{
		if (Game::event.key.keysym.sym == SDLK_w)
		{
			movUp = true;
		}

		if (Game::event.key.keysym.sym == SDLK_s)
		{
			movDown = true;
		}

		if (Game::event.key.keysym.sym == SDLK_a)
		{
			movLeft = true;
		}

		if (Game::event.key.keysym.sym == SDLK_d)
		{
			movRight = true;
		}

	}
	if (Game::event.type == SDL_KEYUP)
	{
		if (Game::event.key.keysym.sym == SDLK_w)
		{
			movUp = false;
		}
		if (Game::event.key.keysym.sym == SDLK_s)
		{
			movDown = false;
		}
		if (Game::event.key.keysym.sym == SDLK_a)
		{
			movLeft = false;
		}
		if (Game::event.key.keysym.sym == SDLK_d)
		{
			movRight = false;
		}
	}
	setVelocityFactor();
	oVelocity->limitSpeed();

	srcRect.h = oSize;
	srcRect.w = oSize;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = oSize;
	destRect.h = oSize;

	// Kolizja z kraw�dziami mapy

	if (xpos > 0 && xpos + destRect.w < map_size_x)
	{
		destRect.x = xpos = xpos + oVelocity->getVelocityX();
	}
	else if ((xpos == 0 && oVelocity->getVelocityX() > 0) || (xpos + destRect.w == map_size_x && oVelocity->getVelocityX() < 0))
	{
		destRect.x = xpos = xpos + oVelocity->getVelocityX();
	}
	else {
		if(xpos < 0)
		destRect.x = xpos = 0;
		if (xpos + destRect.w > map_size_x)
		destRect.x = xpos = map_size_x - destRect.w;

		oVelocity->setVelocityX(0);
	}

	if (ypos > 0 && ypos + destRect.h < map_size_y)
	{
		destRect.y = ypos = ypos + oVelocity->getVelocityY();
	}
	else if ((ypos == 0 && oVelocity->getVelocityY() > 0) || ((ypos + destRect.h == map_size_y && oVelocity->getVelocityY() < 0)))
	{
		destRect.y = ypos = ypos + oVelocity->getVelocityY();
	}
	else {
		if (ypos < 0)
		destRect.y = ypos = 0;
		if (ypos + destRect.h > map_size_y)
	    destRect.y= ypos = map_size_y - destRect.h;

		oVelocity->setVelocityY(0);
	}

	// Kolizja
	collide = false;
	result.x = destRect.x = xpos;
	result.y = destRect.y = ypos;
	for (auto& i : CollidingTiles)
	{
		collidingRect = i->getDestinationRect();

		collide = Collision::checkCollision(collidingRect, destRect);

		if (collide)
		{
			result = Collision::calculateCollision(collidingRect, destRect, oVelocity);
			destRect.x = xpos = result.x;
			destRect.y = ypos = result.y;
		}
	}
}

void Player::Render()
{
	drawingRect = { destRect.x - Game::camera.x, destRect.y - Game::camera.y, destRect.w, destRect.h };
	SDL_RenderCopy(Game::renderer, oTexture, &srcRect, &drawingRect);
}

void Player::setVelocityFactor()
{
	if (movUp)
	{
		oVelocity->moveUp();
	}
	if (movDown)
	{
		oVelocity->moveDown();
	}
	if (movLeft)
	{
		oVelocity->moveLeft();
	}
	if (movRight)
	{
		oVelocity->moveRight();
	}
	// W przypadku gdy nie chcemy porusza� si� ju� po osi X, albo po osi Y stopniowo spowalniamy gracza wzgl�dem tej osi.
	if (!movUp && !movDown && abs(oVelocity->getVelocityY()) > 0)
	{
		oVelocity->applyFrictionY();
	}
	if (!movLeft && !movRight && abs(oVelocity->getVelocityX()) > 0)
	{
		oVelocity->applyFrictionX();
	}

	return;
}

int Player::getPositionX()
{
	return xpos;
}

int Player::getPositionY()
{
	return ypos;
}

void Player::setPositionX(int xpos)
{
	this->xpos = xpos;
}

void Player::setPositionY(int ypos)
{
	this->ypos = ypos;
}

void Player::setMapSize(int size_x, int size_y)
{
	map_size_x = size_x * Tileset::TILE_SIZE - destRect.w;
	map_size_y = size_y * Tileset::TILE_SIZE - destRect.h;
}

void Player::setCollidingTiles(std::vector<class Tile*> tiles)
{
	CollidingTiles = tiles;
}

SDL_Rect Player::getRect()
{
	return destRect;
}

