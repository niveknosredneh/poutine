#include "main.h"
#include "hero.h"

extern SDL_Renderer* gRenderer;

Hero::Hero()
{
    setRED(0);
    setGREEN(255);
    setBLUE(0);
    setXposition(100);
    //setYacceleration(1);

    bulletTimer = 0; // as to not spam bullets

    companionIterator = 0;
    companionPower = false;


}

Hero::~Hero()
{

}

void Hero::jump()
{
    if(collisionFlag == true)
    {
        int jumpStrength = 15;
        if(Xacceleration<0)
        {
            setXvelocity(getXvelocity()+jumpStrength);
        }
        else if(Xacceleration>0)
        {
            setXvelocity(getXvelocity()-jumpStrength);
        }
        if(Yacceleration<0)
        {
            setYvelocity(getYvelocity()+jumpStrength);
        }
        else if(Yacceleration>0)
        {
            setYvelocity(getYvelocity()-jumpStrength);
        }
    }


}

void Hero::moveLeft()
{
    if(collisionFlag)
    {
        hero1.setXvelocity(hero1.getXvelocity()-1);
    }
    if(companionPower)
    {
        hero1.setXvelocity(hero1.getXvelocity()-1);
        companions[companionIterator].setXvelocity(15);
        //companions[companionIterator].setYvelocity(0);

    }
}
void Hero::moveRight()
{
    if(collisionFlag)
    {
        hero1.setXvelocity(hero1.getXvelocity()+1);
    }
    if(companionPower)
    {
        hero1.setXvelocity(hero1.getXvelocity()+1);
        companions[companionIterator].setXvelocity(-15);
        //companions[companionIterator].setYvelocity(0);
    }
}
void Hero::moveUp()
{
    if(collisionFlag)
    {
        hero1.setYvelocity(hero1.getYvelocity()-1);
    }
    if(companionPower)
    {
        hero1.setYvelocity(hero1.getYvelocity()-1);
        companions[companionIterator].setYvelocity(+15);
        //companions[companionIterator].setXvelocity(0);
    }
}
void Hero::moveDown()
{
    if(collisionFlag)
    {
        hero1.setYvelocity(hero1.getYvelocity()+1);
    }
    if(companionPower)
    {
        hero1.setYvelocity(hero1.getYvelocity()+1);
        companions[companionIterator].setYvelocity(-15);
        //companions[companionIterator].setXvelocity(0);
    }


}

void Hero::shoot()
{

    Sprite c1;
    c1.setHeight(3);
    c1.setWidth(3);
    c1.setXposition(getXposition()+(Width/2));
    c1.setYposition(getYposition()+(Height/2));
    if(!(bulletTimer%3)) c1.setBLUE(255);
    else if(!(bulletTimer%5))
        c1.setRED(255);
    else c1.setGREEN(255);
    c1.setXvelocity(1);
    c1.setMaxVelocity(15);
    companions.push_back(c1);

    for (std::vector<Sprite>::size_type i = 0; i <  companions.size(); i++)
    {
        companions[i].setXvelocity(Xvelocity);
        companions[i].setYvelocity(Yvelocity);

    }


}

std::vector<Bullet> Hero::getBullets()
{
	return bullets;
}

void Hero::iterateCompanions()
{
    companionIterator++;
    if(companionIterator > companions.size()) companionIterator = 0;

}

void Hero::updateCompanions()
{

    companionPower = false;


    // dont let them get too far away ... fix off screen issues
    for (std::vector<Sprite>::size_type i = 0; i <  companions.size(); i++)
    {
        companions[i].update(); // update position

        // if hero and companion collide
        SDL_Rect newRect = companions[i].getRect();
        if(Sprite::checkCollision(&newRect) && companions[i].getGREEN()==255)
        {
            companionIterator = i;
            companionPower = true;
            companionColliders.push_back(companions[i]);

        }

        if(companions[i].getXposition() - getXposition() - (Width/2) > 5)
        {
            companions[i].setXvelocity( companions[i].getXvelocity() - (3 + (rand() % 2)));
        }
        else if(companions[i].getXposition() - getXposition() < -5)
        {
            companions[i].setXvelocity( companions[i].getXvelocity() + (3 + (rand() % 2)));
        }
        if(companions[i].getYposition() - getYposition() - (Height/2) > 5)
        {
            companions[i].setYvelocity( companions[i].getYvelocity() - (3 + (rand() % 2)));
        }
        else if(companions[i].getYposition() - getYposition() < -5)
        {
            companions[i].setYvelocity( companions[i].getYvelocity() + (3 + (rand() % 2)));
        }
    }

}



void Hero::renderBullets(int camx, int camy)
{
    // increases bullet timer once per tick
    bulletTimer++;

    for (std::vector<Sprite>::size_type i = 0; i <  companions.size(); i++)
    {
        companions[i].render(camx,camy);
    }

        // render bullets
    for (std::vector<Bullet>::size_type i = 0; i < bullets.size(); i++)
    {

        bullets[i].setLifetime(bullets[i].getLifetime()-1);

        unsigned long life = bullets[i].getLifetime();
        if(life<1 || (bullets[i].getXvelocity()==0 && bullets[i].getYvelocity()==0)) // non moving bullets dissapear too
            bullets.erase(bullets.begin()+i);
        else
        {
            bullets[i].update();
            SDL_Rect SpriteRect = { bullets[i].getXposition()-camx, bullets[i].getYposition()-camy, bullets[i].getWidth(), bullets[i].getHeight() };
            SDL_SetRenderDrawColor( gRenderer, bullets[i].getRED(), bullets[i].getGREEN(), bullets[i].getBLUE(), 0xFF );
            SDL_RenderFillRect( gRenderer, &SpriteRect );
        }
    }


}

bool Hero::checkCollision(SDL_Rect* rect)
{

    for(std::vector<Bullet>::size_type j = 0; j < bullets.size(); j++)
	{
		if (bullets[j].checkCollision(rect))
		{
			bullets.erase(bullets.begin()+j);
		}

	}

	return Sprite::checkCollision(rect);
}
