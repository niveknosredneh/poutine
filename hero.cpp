#include "main.h"
#include "hero.h"

extern SDL_Rect camera;

extern SDL_Renderer* gRenderer;

Hero::Hero()
{
    setRED(0);
    setGREEN(255);
    setBLUE(0);
    setXposition(100);
    //setYacceleration(1);

    bulletTimer = 0; // as to not spam bullets




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

SDL_Rect flame;
void Hero::moveLeft()
{
    Xvelocity--;
    flame = {Xposition+Width - camera.x, Yposition+Height/2 - camera.y, 10, 5};
    SDL_SetRenderDrawColor( gRenderer, 0XFF, 0X00, 0X00, 0xFF );
    SDL_RenderFillRect( gRenderer, &flame );

}
void Hero::moveRight()
{
    Xvelocity++;
    flame = {Xposition - camera.x, Yposition+Height/2 - camera.y, 10, 5};
    SDL_SetRenderDrawColor( gRenderer, 0XFF, 0X00, 0X00, 0xFF );
    SDL_RenderFillRect( gRenderer, &flame );

}
void Hero::moveUp()
{
    Yvelocity--;
    flame = {Xposition+Width/2 - camera.x, Yposition+Height - camera.y, 5, 10};
    SDL_SetRenderDrawColor( gRenderer, 0XFF, 0X00, 0X00, 0xFF );
    SDL_RenderFillRect( gRenderer, &flame );

}
void Hero::moveDown()
{
    Yvelocity++;
    flame = {Xposition+Width/2 - camera.x, Yposition - camera.y, 5, 10};
    SDL_SetRenderDrawColor( gRenderer, 0XFF, 0X00, 0X00, 0xFF );
    SDL_RenderFillRect( gRenderer, &flame );

}

void Hero::shoot()
{
    Bullet newBullet(55);
    newBullet.setGREEN(255);
    newBullet.setXposition(Xposition);
    newBullet.setYposition(Yposition);
    newBullet.setXvelocity(35);


    bullets.push_back(newBullet);


}

std::vector<Bullet> Hero::getBullets()
{
	return bullets;
}




void Hero::renderBullets(int camx, int camy)
{
    // increases bullet timer once per tick
    bulletTimer++;

    // render bullets
    for (std::vector<Bullet>::size_type i = 0; i < bullets.size(); i++)
    {
        bullets[i].update();
        bullets[i].Sprite::update();
        bullets[i].setLifetime(bullets[i].getLifetime()-1);

        unsigned long life = bullets[i].getLifetime();
        if(life<1 || (bullets[i].getXvelocity()==0 || bullets[i].getYvelocity()==0)) // non moving bullets dissapear too
            bullets.erase(bullets.begin()+i);
        else
        {
            bullets[i].render(camx,camy);

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
