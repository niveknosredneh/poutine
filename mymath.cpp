//mymath.cpp
#include "main.h"

// My math functions mostly for polar coordinates
// theta is in RADIANS! unless specified otherwise


SDL_Rect moveOnAngle(SDL_Rect R2, double distance, double theta)
{
    double changeInX, changeInY;
    SDL_Rect newRect = R2;
    changeInX = distance * cos(theta);
    changeInY = distance * sin(theta);

    newRect.x += changeInX;
    newRect.y += changeInY;

    return newRect;
}

SDL_Rect changeAngle(Sprite R1, Sprite R2, double changeInDegrees)
{
    SDL_Rect newRect;

    double theta = getTheta(R2,R1);
    theta += (changeInDegrees * 3.141593/180.0); // conversion from degrees to radians
    double radius = R2.getRad();
    //theta+=2*3.141593;


    newRect.x = R1.getXposition() +  radius * cos(theta);
    newRect.y = R1.getYposition() +  radius * sin(theta);

    return newRect;
}

// get distance between centre points of two rectangles
double getRadius(Sprite R1, Sprite R2)
{
    double radius;

    // Centre to Centre
    // radius = sqrt(x^2 + y^2)
    radius = sqrt(   pow( ( (R1.getXposition() - (R1.getWidth()/2) ) - (R2.getXposition() + (R2.getWidth()/2) ) ) ,2)
                        +
                     pow( ( (R1.getYposition() - (R1.getHeight()/2) ) - (R2.getYposition() + (R2.getHeight()/2) ) ) ,2)
                 );
    DMSG = std::to_string(radius);
    return radius;
}

double getTheta(Sprite R1, Sprite R2)
{
    double x, y;
    x = float( (R1.getXposition() //+ (R1.getWidth()/2) )
    - (R2.getXposition() //+ (R2.getWidth()/2
    ) ) );
    y = float( (R1.getYposition() //+ (R1.getHeight()/2) )
    - (R2.getYposition() //+ (R2.getHeight()/2
    ) ) );
    double theta = atan2(y,x);

    //if(x>0 && y<0) theta+= 3.141593/2;
    //if(x<0 && y<0) theta+= 3.141593;
    //if(x<0 && y>0) theta+= 3*3.141593/2;

    return theta;
}

