#include "main.h"
#include "enemy.h"
#include "timer.h"

extern SDL_Renderer* gRenderer;


Enemy::Enemy()
{

    setRED( (rand() % 155) +100);
    setBLUE(0);
    setGREEN(0);

    setWidth( (rand() % 150) +15);
    setHeight( 15 );

    // default position
    setXposition(rand() % LEVEL_WIDTH);
    setYposition(rand() % LEVEL_HEIGHT);

}

Enemy::~Enemy()
{

}


void Enemy::ifCollision()
{

    Sprite::setRED(getRED()-1);
}

