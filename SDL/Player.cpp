#include "Player.h"

Player::Player(const char* texturesheet, float x, float y)
{
	oTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
	oSize = 64;

	movUp = false;
	movDown = false;
	movLeft = false;
	movRight = false;
	
	oVelocity = new Velocity(0.6f, 0.91f, 10);
}

void Player::Update()
{
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
	destRect.x = xpos = xpos + oVelocity->getVelocityX();
	destRect.y = ypos = ypos + oVelocity->getVelocityY();

}

void Player::Render()
{
	SDL_Rect drawingRect = { destRect.x - Game::camera.x, destRect.y - Game::camera.y, destRect.w, destRect.h };
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
	// W przypadku gdy nie chcemy poruszaæ siê ju¿ po osi X, albo po osi Y stopniowo spowalniamy gracza wzglêdem tej osi.
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

float Player::getPositionX()
{
	return xpos;
}

float Player::getPositionY()
{
	return ypos;
}

void Player::setPositionX(float xpos)
{
	this->xpos = xpos;
}

void Player::setPositionY(float ypos)
{
	this->ypos = ypos;
}
