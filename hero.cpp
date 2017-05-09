#include "main.h"
#include "hero.h"

extern SDL_Rect camera;

extern SDL_Colour cyan;

extern SDL_Renderer* gRenderer;

Hero::Hero()
{
    Colour = cyan;
    Health = 100;
    ShieldHealth = 25;

    Position.x = SCREEN_WIDTH/2.5;
    Position.y = SCREEN_HEIGHT/2.5;

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

void Hero::moveLeft()
{
    Velocity.x--;


}
void Hero::moveRight()
{
    Velocity.x++;


}
void Hero::moveUp()
{
    Velocity.y--;

}
void Hero::moveDown()
{
    Velocity.y++;

}

void Hero::shoot(int x, int y)
{
    Bullet newBullet(300);
    newBullet.setColour({255,50,50});
    newBullet.setPosition({Position.x,Position.y});

    int newXvel,newYvel;

    double theta = getTheta(Position,{x,y});


    newXvel = std::cos(theta) *10 + (getVelocity().x );
    newYvel = std::sin(theta) *10 + (getVelocity().y );
    newBullet.setVelocity({newXvel,newYvel});

    bullets.push_back(newBullet);


}

void Hero::damage(int percent)
{
    Health -= percent;

    if(Health<0)
        mainState=DEATH;
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
        if(life<1)
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
