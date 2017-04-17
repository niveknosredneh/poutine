#include "main.h"
#include "sprite.h"
#include "bullet.h"


Bullet::Bullet(int ticks)
{
	//Initialize
	Width = 2;
	Height = 2;
	Depth = 1; // default

	Mass = 1; // TODO

	// change in position per tick (px/tick)
	Xvelocity = 1;
	Yvelocity = 1;
	maxVelocity = 40;

	// change in velocity per tick (px/tick^2)
	Xacceleration = 0;
	Yacceleration = 0;
	maxAcceleration = 5;

	SpriteRect = {Xposition,Yposition, Width, Height};

	RED =  0xff;
	GREEN = 0x00;
	BLUE = 0x00;

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


