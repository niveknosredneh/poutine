#include "main.h"
#include "sprite.h"


extern SDL_Renderer* gRenderer;

/* from sonic physics
Acceleration (acc), deceleration (dec), and friction (frc) are added to Xsp;
jump velocity (jmp) and gravity (grv) are added to Ysp
*/

Sprite::Sprite()
{
	//Initialize
	Width = 10;
	Height = 10;

	Mass = 1; // TODO

	// position on screen, with origin in top left corner
	Xposition = 50;
	Yposition = 50;

	// change in position per tick (px/tick)
	Xvelocity = 0;
	Yvelocity = 0;
	maxVelocity = 10;

	// change in velocity per tick (px/tick^2)
	Xacceleration = 0;
	Yacceleration = 0;
	maxAcceleration = 5;

	SpriteRect = {Xposition,Yposition, Width, Height};

	RED =  0x00;
	GREEN = 0x00;
	BLUE = 0x00;

	collisionFlag = false;

}

Sprite::~Sprite()
{
	// TODO learn how to clean up properly
}


// updates position on screen and does some other stuff
void Sprite::update()
{

    lastRect = { Xposition, Yposition, Width, Height };

    // off screen conditions
    if(Xposition<0)
		Xposition=0;
    if(Xposition>LEVEL_WIDTH-Width)
        Xposition=LEVEL_WIDTH-Width;
    if(Yposition<0)
		Yposition=0;
    if(Yposition>LEVEL_HEIGHT-Height)
        spawn(25,25);
        //Yposition=LEVEL_HEIGHT-Height;


    lastRect = { Xposition, Yposition, Width, Height };

    setXvelocity(getXvelocity()+Xacceleration);
    setYvelocity(getYvelocity()+Yacceleration);

    Xposition += Xvelocity;
    Yposition += Yvelocity;

    SpriteRect = { Xposition, Yposition, Width, Height };

    // friction..?
    if(collisionFlag)
    {
        if(Xvelocity<0) setXvelocity(getXvelocity()+1);
        else if(Xvelocity>0) setXvelocity(getXvelocity()-1);

        if(Yvelocity<0) setYvelocity(getYvelocity()-1);
        else if(Yvelocity>0) setYvelocity(getYvelocity()+1);
    }


    unsetCollision();

}

void Sprite::render(int camx, int camy)
{

		// render sprite
        SDL_Rect SpriteRect = { Xposition-camx, Yposition-camy, Width, Height };
		SDL_SetRenderDrawColor( gRenderer, RED, GREEN, BLUE, 0xFF );
		SDL_RenderFillRect( gRenderer, &SpriteRect );

        //SDL_RenderDrawRect( gRenderer, &SpriteRect ); //no fill
}


bool Sprite::checkCollision(SDL_Rect* rect)
{

    bool flag = false;
    if ( SDL_HasIntersection(&SpriteRect,rect)==SDL_TRUE )
	{
		flag = true;
		collisionFlag = true;
    }

	return flag;
}


void Sprite::collisionResponse(SDL_Rect newRect)
{
    SDL_Rect collisionRect = getCollision(&newRect);

	if(collisionRect.y + collisionRect.h == newRect.y + newRect.h && collisionRect.w>collisionRect.h) // hits bottom and moving up
	{
		invertYvelocity();
		setYvelocity(0);
		setYposition(getYposition() + collisionRect.h);
	}
	else if(collisionRect.y == newRect.y && collisionRect.w>collisionRect.h) // hits top and moving down
	{
		invertYvelocity();
		setYvelocity(0);
		setYposition(getYposition() - collisionRect.h);
	}
	else if(collisionRect.x + collisionRect.w == newRect.x + newRect.w  && collisionRect.h>collisionRect.w) // hits right and moving left
	{
		invertXvelocity();
		setXvelocity(0);
		setXposition(getXposition() + collisionRect.w);
	}
	else if(collisionRect.x == newRect.x  && collisionRect.h>collisionRect.w) // hits left and moving right
	{
		invertXvelocity();
		setXvelocity(0);
		setXposition(getXposition() - collisionRect.w);
	}


}

void Sprite::setCollision()
{
    collisionFlag = true;
}


SDL_Rect Sprite::getRect()
{
    return SpriteRect;
}

SDL_Rect Sprite::getLastRect()
{
    return lastRect;
}


SDL_Rect Sprite::getCollision(SDL_Rect* rect)
{
    SDL_Rect result;
    SDL_IntersectRect(&SpriteRect,rect,&result);
    return result;
}

void Sprite::spawn(int X, int Y)
{
	Xposition = X;
	Yposition = Y;

}

int Sprite::getXvelocity()
{
	return Xvelocity;

}
int Sprite::getYvelocity()
{
	return Yvelocity;
}

void Sprite::setXvelocity(int amount)
{
	if(amount > maxVelocity)
		Xvelocity = maxVelocity;
	else if(amount < -maxVelocity)
		Xvelocity = -maxVelocity;
	else
		Xvelocity = amount;
}

void Sprite::setYvelocity(int amount)
{
    if(amount > maxVelocity)
		Yvelocity = maxVelocity;
	else if(amount < -maxVelocity)
		Yvelocity = -maxVelocity;
	else
		Yvelocity = amount;
}

void Sprite::setMaxVelocity(int value)
{
	maxVelocity = value;
}

void Sprite::setXacceleration(int amount)
{
	Xacceleration = amount;
}

void Sprite::setYacceleration(int amount)
{
	Yacceleration = amount;
}

int Sprite::getXacceleration()
{
	return Xacceleration;
}

int Sprite::getYacceleration()
{
	return Yacceleration;
}

void Sprite::invertXvelocity()
{
    Xvelocity *= -1;
}

void Sprite::invertYvelocity()
{
    Yvelocity *= -1;
}


int Sprite::getHeight()
{
	return Height;
}
void Sprite::setHeight(int newHeight)
{
	Height = newHeight;

}

int Sprite::getWidth()
{
	return Width;
}
void Sprite::setWidth(int newWidth)
{
	Width = newWidth;

}

int Sprite::getXposition()
{
	return Xposition;
}
int Sprite::getYposition()
{
	return Yposition;
}
void Sprite::setXposition(int newX)
{
	Xposition = newX;
}
void Sprite::setYposition(int newY)
{
	Yposition = newY;
}

int Sprite::getRED()
{
	return RED;
}
void Sprite::setRED(int newRED)
{
	RED = newRED;
}

int Sprite::getBLUE()
{
	return BLUE;
}
void Sprite::setBLUE(int newBLUE)
{
	BLUE = newBLUE;
}

int Sprite::getGREEN()
{
	return GREEN;
}
void Sprite::setGREEN(int newGREEN)
{
	GREEN = newGREEN;
}

void Sprite::unsetCollision()
{
	collisionFlag = false;
}

int Sprite::getMass()
{
	return Mass;
}
