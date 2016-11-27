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
	Width = 20;
	Height = 20;

	// f1 = f1 = constant * m1 * m2 / r^2

	Mass = 1; // TODO

	// position on screen, with origin in top left corner
	Xposition = 50;
	Yposition = 50;

	// change in position per tick (px/tick)
	Xvelocity = 0;
	Yvelocity = 0;
	maxVelocity = 3;

	// change in velocity per tick (px/tick^2)
	Xacceleration = 0;
	Yacceleration = 0;
	maxAcceleration = 2;

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

void Sprite::shoot()
{
	Bullet bullet(100);
	bullet.setRED(hero1.getRED());
	bullet.setGREEN(hero1.getGREEN());
	bullet.setBLUE(hero1.getBLUE());
	bullet.setWidth(Width/10);
	bullet.setMaxVelocity(15);

	bullet.setXposition(Xposition+(Width/2));
	bullet.setYposition(Yposition+(Height/2));

	if(Xvelocity>0)
		bullet.setXvelocity(Xvelocity+3);
	else if(Xvelocity<0)
		bullet.setXvelocity(Xvelocity-3);
	if(Yvelocity>0)
		bullet.setYvelocity(Yvelocity+3);
	else if(Yvelocity<0)
		bullet.setYvelocity(Yvelocity-3);


	bullets.push_back(bullet);
}

std::vector<Bullet> Sprite::getBullets()
{
	return bullets;
}

// updates position on screen and does some other stuff
void Sprite::update()
{

    lastRect = { Xposition, Yposition, Width, Height };

    // off screen conditions
    if(Xposition<0)
		Xposition+=LEVEL_WIDTH;
    if(Xposition>LEVEL_WIDTH-Width)
        Xposition-=LEVEL_WIDTH;
    if(Yposition<0)
		Yposition+=LEVEL_HEIGHT;
    if(Yposition>LEVEL_HEIGHT-Height)
        Yposition-=LEVEL_HEIGHT;

    lastRect = { Xposition, Yposition, Width, Height };

    setXvelocity(getXvelocity()+Xacceleration);
    setYvelocity(getYvelocity()+Yacceleration);

    Xposition += Xvelocity;
    Yposition += Yvelocity;

    SpriteRect = { Xposition, Yposition, Width, Height };

}

void Sprite::render(int camx, int camy)
{
		// render hero
        SDL_Rect SpriteRect = { Xposition-camx, Yposition-camy, Width, Height };
		SDL_SetRenderDrawColor( gRenderer, RED, GREEN, BLUE, 0xFF );
		SDL_RenderFillRect( gRenderer, &SpriteRect );

		// render bullets
		for (std::vector<Bullet>::size_type i = 0; i < bullets.size(); i++)
		{

			bullets[i].setLifetime(bullets[i].getLifetime()-1);

			unsigned long life = bullets[i].getLifetime();
			if(life<1 || (bullets[i].getXvelocity()==0 && bullets[i].getYvelocity()==0)) // non moving bullets dissapear too
				bullets.erase(bullets.begin()+i);
			else
			{
				bullets[i].Sprite::update();
				filledCircleRGBA(gRenderer, bullets[i].getXposition()-camx,
					bullets[i].getYposition()-camy, bullets[i].getWidth(), bullets[i].getRED(), bullets[i].getGREEN(),bullets[i].getBLUE(), 0xff);
			}
		}

        //SDL_RenderDrawRect( gRenderer, &SpriteRect ); //no fill
}


bool Sprite::checkCollision(SDL_Rect* rect)
{

    collisionFlag = false;
    if ( SDL_HasIntersection(&SpriteRect,rect)==SDL_TRUE )
	{
		collisionFlag = true;
    }

    for(std::vector<Bullet>::size_type j = 0; j < bullets.size(); j++)
	{
		if (bullets[j].checkCollision(rect))
		{
			bullets.erase(bullets.begin()+j);
		}
	}

	return collisionFlag;
}


void Sprite::collisionResponse(SDL_Rect newRect)
{
    SDL_Rect collisionRect = getCollision(&newRect);

	if(collisionRect.y + collisionRect.h == newRect.y + newRect.h && collisionRect.w>collisionRect.h) // hits bottom and moving up
	{
		invertYvelocity();
		setYvelocity(Yvelocity+1);
		setYposition(getYposition() + collisionRect.h);
	}
	else if(collisionRect.y == newRect.y && collisionRect.w>collisionRect.h) // hits top and moving down
	{
		invertYvelocity();
		setYvelocity(Yvelocity-1);
		setYposition(getYposition() - collisionRect.h);
	}
	else if(collisionRect.x + collisionRect.w == newRect.x + newRect.w  && collisionRect.h>collisionRect.w) // hits right and moving left
	{
		invertXvelocity();
		setXvelocity(Xvelocity-1);
		setXposition(getXposition() + collisionRect.w);
	}
	else if(collisionRect.x == newRect.x  && collisionRect.h>collisionRect.w) // hits left and moving right
	{
		invertXvelocity();
		setXvelocity(Xvelocity+1);
		setXposition(getXposition() - collisionRect.w);
	}
	else if(collisionRect.h==collisionRect.w)
	{
		//invertXvelocity();
		//invertYvelocity();
		//filledCircleColor(gRenderer, getXposition()+getWidth()/2, getYposition()+getHeight()/2, getWidth()/2, 0xFF0000FF);
	}

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
