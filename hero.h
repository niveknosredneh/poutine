#ifndef HERO_H
#define HERO_H

class Hero : public Sprite
{
	private:

        std::vector<Bullet> bullets;
        std::vector<Sprite> companions;

        unsigned long bulletTimer;

        std::vector<Sprite>::size_type companionIterator;
        bool companionPower;
        std::vector<Sprite> companionColliders;


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

		void updateCompanions();

		void iterateCompanions();

		std::vector<Bullet> getBullets();
		bool checkCollision(SDL_Rect* rect);

};

#endif
