#ifndef ENEMY_H
#define ENEMY_H


class Enemy : public Sprite
{

    private:

        unsigned int maxTicks;
        unsigned int tickCounter;

	public:
		//Initializes variables
		Enemy();

		//Deallocates memory
		~Enemy();

		void ifCollision();

};

#endif
