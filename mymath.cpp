//mymath.cpp
#include "main.h"

// My math functions mostly for polar coordinates
// theta is in RADIANS! unless specified otherwise


SDL_Rect changeAngle(Sprite R1, Sprite R2, double changeInDegrees)
{
    SDL_Rect newRect;

    double theta = getTheta(R2,R1);
    theta += (changeInDegrees * 3.141593/180.0); // conversion from degrees to radians
    double radius = R2.getRad();

    double newX = R1.getCentre().x;
    double newY = R1.getCentre().y;
    newRect.x = newX - R2.getWidth().x/2 - radius * cos(theta);
    newRect.y = newY - R2.getWidth().y/2 - radius * sin(theta);

    return newRect;
}

// get distance between centre points of two rectangles
double getRadius(Sprite R1, Sprite R2)
{
    double radius;

    // Centre to Centre
    // radius = sqrt(x^2 + y^2)
    radius = sqrt(   pow( R2.getCentre().x - R1.getCentre().x  ,2)
                        +
                     pow( R2.getCentre().y - R1.getCentre().y  ,2)
                 );
    return radius;
}

double getTheta(Sprite R1, Sprite R2)
{
    double x, y;
    x = float( R2.getCentre().x - R1.getCentre().x );
    y = float( R2.getCentre().y - R1.getCentre().y );
    double theta = atan2(y,x);


    return theta;
}

