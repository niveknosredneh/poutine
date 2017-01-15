#ifndef HERO_H
#define HERO_H

class Hero : public Sprite
{
	private:

        std::vector<Bullet> bullets;
        std::vector<Sprite> companions;

        unsigned long bulletTimer;


	public:
		//Initializes variables
		Hero();

		//Deallocates memory
		~Hero();

        void jump();
		void shoot();

		void renderBullets(int,int);

		void updateCompanions();

		std::vector<Bullet> getBullets();
		bool checkCollision(SDL_Rect* rect);

};

#endif
