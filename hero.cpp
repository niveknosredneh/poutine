#include "main.h"
#include "hero.h"

extern SDL_Rect camera;

extern SDL_Renderer* gRenderer;

Hero::Hero()
{
    Colour = {0,255,0};
    Health = 100;
    ShieldHealth = 25;

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
        if(Acceleration.x<0)
        {
            Velocity.x += jumpStrength;
        }
        else if(Acceleration.x>0)
        {
            Velocity.x -= jumpStrength;
        }
        if(Acceleration.y<0)
        {
            Velocity.y += jumpStrength;
        }
        else if(Acceleration.y>0)
        {
            Velocity.y -= jumpStrength;
        }
    }
}

SDL_Rect flame;
void Hero::moveLeft()
{
    Velocity.x--;
    flame = {Position.x + Width.x/2 - camera.x, Position.y + Width.y/2 - camera.y, 10, 5};
    SDL_SetRenderDrawColor( gRenderer, 0XFF, 0X00, 0X00, 0xFF );
    SDL_RenderFillRect( gRenderer, &flame );

}
void Hero::moveRight()
{
    Velocity.x++;
    flame = {Position.x - Width.x/2 - camera.x, Position.y + Width.y/2- camera.y, 10, 5};
    SDL_SetRenderDrawColor( gRenderer, 0XFF, 0X00, 0X00, 0xFF );
    SDL_RenderFillRect( gRenderer, &flame );

}
void Hero::moveUp()
{
    Velocity.y--;
    flame = {Position.x+Width.x/2 - camera.x, Position.y + Width.y/2 - camera.y, 5, 10};
    SDL_SetRenderDrawColor( gRenderer, 0XFF, 0X00, 0X00, 0xFF );
    SDL_RenderFillRect( gRenderer, &flame );

}
void Hero::moveDown()
{
    Velocity.y++;
    flame = {Position.x+Width.x/2 - camera.x, Position.y - Width.y/2 - camera.y, 5, 10};
    SDL_SetRenderDrawColor( gRenderer, 0XFF, 0X00, 0X00, 0xFF );
    SDL_RenderFillRect( gRenderer, &flame );

}

void Hero::shoot()
{
    Bullet newBullet(55);
    newBullet.setColour({0,255,0});
    newBullet.setPosition({Position.x,Position.y});
    newBullet.setVelocity({10,0});


    bullets.push_back(newBullet);


}

std::vector<Bullet> Hero::getBullets()
{
	return bullets;
}

double Hero::getHealth()
{
    return Health;
}



void Hero::renderBullets(int camx, int camy)
{
    // increases bullet timer once per tick
    bulletTimer++;

    // render bullets
    for (std::vector<Bullet>::size_type i = 0; i < bullets.size(); i++)
    {
        bullets[i].Sprite::update();
        bullets[i].Bullet::update();

        unsigned long life = bullets[i].getLifetime();
        if(life<1 || (bullets[i].getVelocity().x==0 || bullets[i].getVelocity().y==0)) // non moving bullets dissapear too
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
