#pragma once

class Velocity
{
public:
	
	Velocity(float accel, float friction, float vMax);
	~Velocity();
	float getVelocityX();
	float getVelocityY();
	void setVelocityX(float x);
	void setVelocityY(float y);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void applyFrictionX();
	void applyFrictionY();
	void limitSpeed();

private:
	
	float x;
	float y;

	float accel;
	float friction;
	float vMax;
};

