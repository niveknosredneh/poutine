#include "main.h"
#include "wall.h"


extern SDL_Renderer* gRenderer;
extern Hero hero1;


Wall::Wall(int X, int Y, int length, bool vertical)
{

	// position on screen, with origin in top left corner
	Xposition = X;
	Yposition = Y;

    int wallBuffer = 10; // placer, please use data oriented

    if(vertical)
    {
        Width = wallBuffer;
        Height = length;
    }
    else
    {
        Width = length;
        Height = wallBuffer;
    }

	SDL_Rect wallRect = {X,Y,Width,Height};

	RED =  0x00;
	GREEN = 0x00;
	BLUE = 0x00;

    isVertical = vertical;


}

Wall::~Wall()
{

}


void Wall::getRect(SDL_Rect &rect)
{
    rect.x = Xposition;
    rect.y = Yposition;
    rect.w = Width;
    rect.h = Height;
}

void Wall::render(int camX, int camY)
{

    SDL_Rect newRect = {Xposition-camX, Yposition-camY, Width, Height};
    SDL_SetRenderDrawColor( gRenderer, RED, BLUE, GREEN, 0xFF );
    SDL_RenderFillRect( gRenderer, &newRect );

}

bool Wall::getVertical()
{
	bool vertical = false;

    if(isVertical)
		return true;

}



