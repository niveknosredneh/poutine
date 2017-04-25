#ifndef HERO_H
#define HERO_H

class Hero : public Sprite
{
	private:

        double Health;
        double ShieldHealth;

        std::vector<Bullet> bullets;


        unsigned long bulletTimer;




	public:
		//Initializes variables
		Hero();

		//Deallocates memory
		~Hero();

        void jump();
		void shoot();

		void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

		void renderBullets(int,int);

		double getHealth();



		std::vector<Bullet> getBullets();
		bool checkCollision(SDL_Rect* rect);

};

#endif
