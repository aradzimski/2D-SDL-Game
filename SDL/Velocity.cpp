#include "Velocity.h"
#include <iostream>

Velocity::Velocity(float accel, float friction, float vMax)
{
	this->accel = accel;
	this->friction = friction;
	this->vMax = vMax;
	x = 0;
	y = 0;
}

Velocity::~Velocity()
{
}

float Velocity::getVelocityX()
{
	return x;
}

float Velocity::getVelocityY()
{
	return y;
}

void Velocity::setVelocityX(float x)
{
	this->x = x;
}

void Velocity::setVelocityY(float y)
{
	this->y = y;
}

void Velocity::moveUp()
{
   y -= accel;
}

void Velocity::moveDown()
{
	y += accel;
}

void Velocity::moveLeft()
{
	x -= accel;
}

void Velocity::moveRight()
{
	x += accel;
}

void Velocity::applyFrictionX()
{
	x *= friction;
	if (abs(x) < 2)
	{
		x = 0;
	}
}

void Velocity::applyFrictionY()
{
	y *= friction;
	if (abs(y) < 2)
	{
		y = 0;
	}
}

void Velocity::limitSpeed()
{
	if (abs(x) > vMax)
	{
		x = (vMax * x) / abs(x);
	}

	if (abs(y) > vMax)
	{
		y = (vMax * y) / abs(y);
	}
}