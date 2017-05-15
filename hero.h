#ifndef HERO_H
#define HERO_H

class Hero : public Sprite
{
	private:

        int R,G,B; // powerups

        double Health;
        double ShieldCharge;

        std::vector<Bullet> bullets;


        unsigned long bulletTimer;




	public:
		//Initializes variables
		Hero();

		//Deallocates memory
		~Hero();

        void jump();
		void shoot(int x, int y);

		void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

		void renderBullets(int,int);

		double getHealth();
		void damage(int percent);
		void chargeShield();
		double getShieldCharge();

		void setR(int value);
		void setG(int value);
		void setB(int value);

		int getR();
		int getG();
		int getB();


		std::vector<Bullet> getBullets();
		bool checkCollision(SDL_Rect* rect);

};

#endif
