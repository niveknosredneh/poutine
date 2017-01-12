#include "main.h"
#include "hero.h"


extern SDL_Renderer* gRenderer;

Hero::Hero()
{
    setRED(0);
    setGREEN(255);
    setBLUE(0);
    setXposition(100);
    setYacceleration(1);

}

Hero::~Hero()
{

}

void Hero::ifCollision()
{

    // spawn back to previous location
    //spawn(lastRect.x,lastRect.y);
    // used to stop passing through objects

}
