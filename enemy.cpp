#include "main.h"
#include "enemy.h"
#include "timer.h"

extern SDL_Renderer* gRenderer;


Planet::Planet(int planetID)
{

    long distFrSun;
    int radius;
    int ID = planetID;

    if(planetID==0) // SUN
    {
        setRED(250);
        setBLUE(5);
        setGREEN(255);

        // x 10 000 km
        radius = 70;
        distFrSun = 0;
    }
    if(planetID==1) // Earth
    {
        setRED(2);
        setBLUE(255);
        setGREEN(10);

        radius = 20; // x 1000 km
        distFrSun = 200; // x

    }
    if(planetID==2) // Mars
    {
        setRED(20);
        setBLUE(8);
        setGREEN(8);

        radius = 30; // x 1000 km
        distFrSun = 300; // x


    }
    if(planetID==3)
    {


    }
    if(planetID==4)
    {


    }

    setHeight(radius*2);
    setWidth(radius*2);
    setXposition(distFrSun + 1000);
    setYposition(distFrSun + 1000);

}

Planet::~Planet()
{

}


void Planet::ifCollision()
{

    Sprite::setRED(getRED()-10);
}

