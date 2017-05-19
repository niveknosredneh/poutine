#include "main.h"
#include "hero.h"

extern SDL_Rect camera;

extern SDL_Colour darkgray;

extern SDL_Renderer* gRenderer;

extern double ZOOMx;

Hero::Hero()
{
    R = 15;
    G = 127;
    B = 15;


    Colour = darkgray;
    Health = 128;

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
    if(ShieldCharge==0 && bulletTimer > 5 / R) // only allow shooting if shield is down
    {
        Bullet newBullet(100);
        newBullet.setColour({255,50,50});
        newBullet.setPosition({Position.x,Position.y});

        int newXvel,newYvel;

        double theta = getTheta(Position,{x , y });

        newXvel = std::cos(theta) *10 + Velocity.x ;
        newYvel = std::sin(theta) *10 + Velocity.y ;
        newBullet.setVelocity({newXvel,newYvel});

        bullets.push_back(newBullet);
        bulletTimer=0;
    }
}

void Hero::damage(int percent)
{

    int value = percent;
    if(ShieldCharge>0)
    {
        ShieldCharge-=value;
        if(ShieldCharge<0)
        {
            Health += ShieldCharge;
            ShieldCharge=0;
        }
    }
    else Health-=value;

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

double Hero::getShieldCharge()
{
    return ShieldCharge;
}

void Hero::chargeShield()
{
    if(ShieldCharge < G) ShieldCharge+=5;

}

void Hero::setR(int value) { R = value; }
void Hero::setG(int value) { G = value; }
void Hero::setB(int value) { B = value; }

int Hero::getR() { return R; }
int Hero::getG() { return G; }
int Hero::getB() { return B; }



void Hero::renderBullets(int camx, int camy)
{
    if(ShieldCharge>0)
    {
        if(ShieldCharge>1) ShieldCharge-=3; else if(ShieldCharge<3) ShieldCharge=0; // deplete shield naturally
        // render shield particles
        SDL_SetRenderDrawColor(gRenderer,0,63 + 3*ShieldCharge/4,0,255);
        for(int i = -ShieldCharge;i <= ShieldCharge;i++)
        {
            SDL_RenderDrawPoint(gRenderer,hero1.getPosition().x + (rand() % 5 + 10 )*cos(i) - camera.x, hero1.getPosition().y + (rand() % 5 + 10 )*sin(i) - camera.y);
        }
    }

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
            bullets[i].render(1,1,false,0,0);

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
