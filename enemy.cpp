#include "main.h"
#include "enemy.h"
#include "timer.h"

extern SDL_Renderer* gRenderer;


Enemy::Enemy()
{

    setRED(255);
    setBLUE(0);
    setGREEN(0);

    setWidth( (rand() % 80) +10);
    setHeight( (rand() % 80) +10);

    // default position
    setXposition(rand() % LEVEL_WIDTH);
    setYposition(rand() % LEVEL_HEIGHT);

}

Enemy::~Enemy()
{

}

void Enemy::ifCollision(SDL_Rect* rect)
{

    // spawn back to previous location
    // used to stop passing through objects
    Xvelocity-=2;
    Yvelocity-=2;
    spawn(lastRect.x,lastRect.y);

}
