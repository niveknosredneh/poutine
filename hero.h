#ifndef HERO_H
#define HERO_H

class Hero : public Sprite
{
	private:

		
	public:
		//Initializes variables
		Hero();

		//Deallocates memory
		~Hero();

		void ifCollision();

};

#endif
