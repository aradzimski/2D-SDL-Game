#include "Collision.h"

bool Collision::checkCollision(SDL_Rect A, SDL_Rect B)
{
	// Nie sprawdzamy dok³adnie kolizji (a przy okazji wywo³ujemy lekki efekt drgania, przy poruszaniu siê przy krawêdziach

	if (
		A.x + A.w > B.x + 2&&
		B.x + B.w > A.x + 2&&
		A.y + A.h > B.y + 2&&
		B.y + B.h > A.y + 2
		)
	{
		return true;
	}

	return false;
}

bool Collision::checkEnemyCollision(SDL_Rect enemy, SDL_Rect player)
{

	// Wersja kolizji z u³atwieniem dla gracza (nie wymaga a¿ takiej precyzji w pozycjonowaniu
	if (
		enemy.x + enemy.w > player.x + 8 &&
		player.x + player.w > enemy.x + 8&&
		enemy.y + enemy.h > player.y + 8 &&
		player.y + player.h > enemy.y + 8
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

		else if (A.x > B.x && (B.y - A.y) < (A.x - B.x))
		{
			result.x = A.x - B.w;
			velocity->setVelocityX(0);
		}

		// Zwyk³a kolizja z do³u

		else if ((B.y - A.y) >= (A.x - B.x))
		{
			result.y = A.y + A.h;
			velocity->setVelocityY(0);
		}
	}

	// Kolizja z góry

	else if (A.y >= B.y)
	{

		// Kolizja z prawej

		if (A.x < B.x && (A.y - B.y) <= (B.x - A.x))
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

		else if ((A.y - B.y) >= (A.x - B.x))
		{
			result.y = A.y - B.h;
			velocity->setVelocityY(0);
		}
	}

	return result;
}

SDL_Rect Collision::calculateEnemyCollision(SDL_Rect A, SDL_Rect B, Velocity* velocity, Enemy* enemy)
{
	SDL_Rect result;
	result.x = B.x;
	result.y = B.y;

	// Kolizja z do³u

	if (A.y < B.y)
	{
		// Kolizja z prawej

		if (A.x < B.x && (B.y - A.y) <= (B.x - A.x))
		{
			result.x = A.x + A.w;
			velocity->setVelocityX(0);
			enemy->movRight = true;
			enemy->movLeft = false;
		}

		// Kolizja z lewej

		else if (A.x > B.x && (B.y - A.y) <= (A.x - B.x))
		{
			result.x = A.x - B.w;
			velocity->setVelocityX(0);
			enemy->movRight = false;
			enemy->movLeft = true;
		}

		// Zwyk³a kolizja z do³u

		else if ((B.y - A.y) > (A.x - B.x))
		{
			result.y = A.y + A.h;
			velocity->setVelocityY(0);
			enemy->movUp = false;
			enemy->movDown = true;
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
			enemy->movRight = true;
			enemy->movLeft = false;
		}

		// Kolizja z lewej

		else if (A.x > B.x && (A.y - B.y) < (A.x - B.x))
		{
			result.x = A.x - B.w;
			velocity->setVelocityX(0);
			enemy->movRight = false;
			enemy->movLeft = true;
		}

		// Zwyk³a kolizja z góry

		else if ((A.y - B.y) > (A.x - B.x))
		{
			result.y = A.y - B.h;
			velocity->setVelocityY(0);
			enemy->movUp = true;
			enemy->movDown = false;
		}
	}

	return result;
}
