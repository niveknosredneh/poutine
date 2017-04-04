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

SDL_Rect changeAngle(SDL_Rect R1, SDL_Rect R2, double changeInDegrees)
{
    SDL_Rect newRect;

    double theta = getTheta(R2,R1);
    theta += (changeInDegrees * 3.141593/180.0); // conversion from degrees to radians
    DMSG = std::to_string(theta);
    double radius = getRadius(R1,R2);
    //theta+=2*3.141593;


    newRect.x = R1.x + radius * cos(theta);
    newRect.y = R1.y + radius * sin(theta);

    return newRect;
}

// get distance between centre points of two rectangles
double getRadius(SDL_Rect R1, SDL_Rect R2)
{
    double radius;

    // Centre to Centre
    // radius = sqrt(x^2 + y^2)
    radius = sqrt(   pow( ( (R1.x + (R1.w/2) ) - (R2.x + (R2.w/2) ) ) ,2)
                        +
                     pow( ( (R1.y + (R1.h/2) ) - (R2.y + (R2.h/2) ) ) ,2)
                 );

    return radius;
}

double getTheta(SDL_Rect R1, SDL_Rect R2)
{
    double x, y;
    x = float( (R1.y ) - (R2.y ) );
    y = float( (R1.x ) - (R2.x ) );
    double theta = atan2(x,y);

    //if(x>0 && y<0) theta+= 3.141593/2;
    //if(x<0 && y<0) theta+= 3.141593;
    //if(x<0 && y>0) theta+= 3*3.141593/2;

    return theta;
}

