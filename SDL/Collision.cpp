#include "Collision.h"

bool Collision::checkCollision(SDL_Rect A, SDL_Rect B)
{
	if (
		A.x + A.w >= B.x &&
		B.x + B.w >= A.x &&
		A.y + A.h >= B.y &&
		B.y + B.h >= A.y
		)
	{
		return true;
	}

	return false;
}

SDL_Rect Collision::calculateCollision(SDL_Rect A, SDL_Rect B)
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
			std::cout << "Kolizja z prawej: " << (A.x + A.w) << " " << B.x << std::endl;
		}

		// Kolizja z lewej

		else if (A.x > B.x && (B.y - A.y) < (A.x - B.x))
		{
			std::cout << "Kolizja z lewej " << A.x << " " << (B.x + B.w) << std::endl;
		}

		// Zwyk³a kolizja z do³u

		else
		{
			std::cout << "Kolizja z dolu " << A.y << " " << B.y << std::endl;
		}
	}

	// Kolizja z góry

	else if (A.y > B.y)
	{

		// Kolizja z prawej

		if (A.x < B.x && (A.y - B.y) < (B.x - A.x))
		{
			std::cout << "Kolizja z prawej: " << (A.x + A.w) << " " << B.x << std::endl;
		}

		// Kolizja z lewej

		else if (A.x > B.x && (A.y - B.y) < (A.x - B.x))
		{
			std::cout << "Kolizja z lewej " << A.x << " " << (B.x + B.w) << std::endl;
		}

		// Zwyk³a kolizja z góry

		else 
		{
			std::cout << "Kolizja z gory " << A.y << " " << B.y << std::endl;
		}
	}

	return result;
}
