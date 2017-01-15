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

    bulletTimer = 0; // as to not spam bullets





}

Hero::~Hero()
{

}

void Hero::jump()
{



}

void Hero::shoot()
{

    Sprite c1;
    c1.setHeight(5);
    c1.setWidth(5);
    c1.setXposition(getXposition()+(rand() % 45));
    c1.setYposition(getYposition()+(rand() % 45));
    c1.setBLUE(255);
    c1.setXvelocity(1);

    companions.push_back(c1);


    if(bulletTimer > 3)
    {
        Bullet bullet(100);

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
        bulletTimer = 0;
    }

}

std::vector<Bullet> Hero::getBullets()
{
	return bullets;
}

void Hero::updateCompanions()
{
    for (std::vector<Sprite>::size_type i = 0; i <  companions.size(); i++)
    {
        companions[i].update();

        if(companions[i].getXposition() - getXposition() > 15)
        {
            companions[i].setXvelocity(companions[i].getXvelocity()-(rand() % 2));
        }
        else if(companions[i].getXposition() - getXposition() < -15)
        {
            companions[i].setXvelocity(companions[i].getXvelocity()+(rand() % 2));
        }
        if(companions[i].getYposition() - getYposition() > 15)
        {
            companions[i].setYvelocity(companions[i].getYvelocity()-(rand() % 2));
        }
        else if(companions[i].getYposition() - getYposition() < -15)
        {
            companions[i].setYvelocity(companions[i].getYvelocity()+(rand() % 2));
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
