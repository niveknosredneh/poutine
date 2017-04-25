#include "main.h"
#include "sprite.h"
#include "bullet.h"


Bullet::Bullet(int ticks)
{
	//Initialize
	Width.x = 2;
	Width.y = 2;
	Depth = 1; // default

	Mass = 1; // TODO

	// change in position per tick (px/tick)
	Velocity.x = 1;
	Velocity.y = 1;
	maxVelocity = 40;

	// change in velocity per tick (px/tick^2)
	Acceleration.x = 0;
	Acceleration.y = 0;
	maxAcceleration = 5;

	SpRect = {Position.x,Position.y, Width.x, Width.y};

	Colour = {0,0,255};

    label = "null";
	collisionFlag = false;

	lifetime = ticks;

}

Bullet::~Bullet()
{

}

void Bullet::update()
{
	lifetime=lifetime-1;

}


unsigned int Bullet::getLifetime()
{
	return lifetime;
}

void Bullet::setLifetime(unsigned int newLife)
{
	lifetime = newLife;
}


