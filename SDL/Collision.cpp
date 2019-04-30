#include "Collision.h"

bool Collision::checkCollision(SDL_Rect A, SDL_Rect B)
{
	if (
		A.x + A.w > B.x &&
		B.x + B.w > A.x &&
		A.y + A.h > B.y &&
		B.y + B.h > A.y
		)
	{
		return true;
	}

	return false;
}

SDL_Rect Collision::calculateCollision(SDL_Rect A, SDL_Rect B, Velocity* velocity)
{
	SDL_Rect result;
	result.x = B.x;
	result.y = B.y;

	// Kolizja z do³u

	if (A.y < B.y)
	{
		// Kolizja z prawej

		if (A.x < B.x && (B.y - A.y) < (B.x - A.x))
		{
			result.x = A.x + A.w;
			velocity->setVelocityX(0);
		}

		// Kolizja z lewej

		else if (A.x > B.x && (B.y - A.y) <= (A.x - B.x))
		{
			result.x = A.x - B.w;
			velocity->setVelocityX(0);
		}

		// Zwyk³a kolizja z do³u

		else if ((B.y - A.y) > (A.x - B.x))
		{
			result.y = A.y + A.h;
			velocity->setVelocityY(0);
		}
	}

	// Kolizja z góry

	else if (A.y >= B.y)
	{

		// Kolizja z prawej

		if (A.x < B.x && (A.y - B.y) < (B.x - A.x))
		{
			result.x = A.x + A.w;
			velocity->setVelocityX(0);
		}

		// Kolizja z lewej

		else if (A.x > B.x && (A.y - B.y) <= (A.x - B.x))
		{
			result.x = A.x - B.w;
			velocity->setVelocityX(0);
		}

		// Zwyk³a kolizja z góry

		else if ((A.y - B.y) > (A.x - B.x))
		{
			result.y = A.y - B.h;
			velocity->setVelocityY(0);
		}
	}

	return result;
}
