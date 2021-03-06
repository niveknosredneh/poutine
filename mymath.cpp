//mymath.cpp
#include "main.h"

// My math functions mostly for polar coordinates
// theta is in RADIANS! unless specified otherwise

//A circle stucture
struct Circle
{
    int x, y;
    int r;
};

// generic vector
struct Vect
{
    double x, y;
};

struct Line
{
    int x1,y1,x2,y2;
};


// Midpoint circle algorithm using lines to fill
// to have unfilled, draw individual points at each of the line points
// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void DrawCircle(int x0,int y0,int r,SDL_Colour colour)
{

    SDL_SetRenderDrawColor( gRenderer, colour.r, colour.g, colour.b, 0xFF );

    int x = r;
    int y = 0;
    int err = 0;

    while (x >= y)
    {

        SDL_RenderDrawLine(gRenderer, x0 + x, y0 + y, x0 - x, y0 + y);
        SDL_RenderDrawLine(gRenderer, x0 + y, y0 + x, x0 - y, y0 + x);
        SDL_RenderDrawLine(gRenderer, x0 - x, y0 - y, x0 + x, y0 - y);
        SDL_RenderDrawLine(gRenderer, x0 + y, y0 - x, x0 - y, y0 - x);

        y += 1;
        if (err <= 0)
        {
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }

}


SDL_Point changeAngle(SDL_Point P1, SDL_Point P2, double Rad, double changeInDegrees)
{
    SDL_Point newP;

    double theta = getTheta(P2,P1);
    theta += (changeInDegrees * 3.141593/180.0); // conversion from degrees to radians

    newP.x = P1.x - Rad * cos(theta);
    newP.y = P1.y - Rad * sin(theta);

    return newP;
}

// get distance between centre points of two rectangles
double getRadius(SDL_Point P1, SDL_Point P2)
{
    double radius;

    // Centre to Centre
    // radius = sqrt(x^2 + y^2)
    radius = sqrt(   pow( P1.x - P2.x  ,2)
                        +
                     pow( P1.y - P2.y  ,2)
                 );
    return radius;
}

double getTheta(SDL_Point P1, SDL_Point P2)
{
    double x, y;
    x = float( P2.x - P1.x );
    y = float( P2.y - P1.y );
    double theta = atan2(y,x);


    return theta;
}

bool checkCollision(Sprite S1, Sprite S2)
{
    bool isCollision = false;

    if( (int)getRadius(S1.getPosition(), S2.getPosition()) < ( S1.getWidth().x/2 + S2.getWidth().x/2 ))
        isCollision=true;

    return isCollision;
}

