#include "Enemy.h"
#include "Collision.h"

Enemy::Enemy(const char* texturesheet, int x, int y, bool movUp, bool movDown, bool movLeft, bool movRight, int speed, bool animated)
{
	oTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;

	this->animated = animated;

	oSize = 64;

	this->movUp = movUp;
	this->movDown = movDown;
	this->movLeft = movLeft;
	this->movRight = movRight;

	oVelocity = new Velocity(0.6f, 0.91f, speed);
}

Enemy::Enemy(const char* texturesheet, int x, int y, bool movUp, bool movDown, bool movLeft, bool movRight, int speed, bool animated, Animation* animation)
{
	oTexture = TextureManager::LoadTexture(texturesheet);
	this->animation = animation;

	xpos = x;
	ypos = y;

	this->animated = animated;

	oSize = 64;

	this->movUp = movUp;
	this->movDown = movDown;
	this->movLeft = movLeft;
	this->movRight = movRight;

	oVelocity = new Velocity(0.6f, 0.91f, speed);
}

void Enemy::Update()
{

	if (animated)
	{
		oTexture = animation->getNextSprite();
	}

	setVelocityFactor();
	oVelocity->limitSpeed();

	srcRect.h = oSize;
	srcRect.w = oSize;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = oSize;
	destRect.h = oSize;

	// Kolizja z krawędziami mapy

	if (xpos > 0 && xpos + destRect.w < map_size_x)
	{
		destRect.x = xpos = xpos + oVelocity->getVelocityX();
	}
	else if ((xpos == 0 && oVelocity->getVelocityX() > 0) || (xpos + destRect.w == map_size_x && oVelocity->getVelocityX() < 0))
	{
		destRect.x = xpos = xpos + oVelocity->getVelocityX();
	}
	else {
		if (xpos <= 0)
		{
			destRect.x = xpos = 0;
			movLeft = false;
			movRight = true;
		}
		if (xpos + destRect.w >= map_size_x)
		{
			destRect.x = xpos = map_size_x - destRect.w;
			movLeft = true;
			movRight = false;
		}

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
		if (ypos <= 0)
		{
			destRect.y = ypos = 0;
			movUp = false;
			movDown = true;
		}
		if (ypos + destRect.h >= map_size_y)
		{
			destRect.y = ypos = map_size_y - destRect.h;
			movUp = true;
			movDown = false;
		}

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
			result = Collision::calculateEnemyCollision(collidingRect, destRect, oVelocity, this);
			destRect.x = xpos = result.x;
			destRect.y = ypos = result.y;
		}
	}
}

void Enemy::Render()
{
	drawingRect = { destRect.x - Game::camera.x, destRect.y - Game::camera.y, destRect.w, destRect.h };
	SDL_RenderCopy(Game::renderer, oTexture, &srcRect, &drawingRect);
}

void Enemy::setVelocityFactor()
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

int Enemy::getPositionX()
{
	return xpos;
}

int Enemy::getPositionY()
{
	return ypos;
}

void Enemy::setPositionX(int xpos)
{
	this->xpos = xpos;
}

void Enemy::setPositionY(int ypos)
{
	this->ypos = ypos;
}

void Enemy::setMapSize(int size_x, int size_y)
{
	map_size_x = size_x * Tileset::TILE_SIZE - destRect.w;
	map_size_y = size_y * Tileset::TILE_SIZE - destRect.h;
}

void Enemy::setCollidingTiles(std::vector<class Tile*> tiles)
{
	CollidingTiles = tiles;
}

SDL_Rect Enemy::getRect()
{
	return destRect;
}
