#ifndef Planet_H
#define Planet_H


class Planet : public Sprite
{

    private:

        unsigned int maxTicks;
        unsigned int tickCounter;

	public:
		//Initializes variables
		Planet(int);

		//Deallocates memory
		~Planet();

		void ifCollision();

};

#endif
