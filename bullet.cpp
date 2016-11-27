#include "main.h"
#include "sprite.h"
#include "bullet.h"


Bullet::Bullet(int ticks)
{
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


