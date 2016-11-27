#ifndef BULLET_H
#define BULLET_H

class Bullet : public Sprite
{
	private:

		unsigned int lifetime; // in ticks

	public:
		//Initializes variables
		Bullet(int);

		//Deallocates memory
		~Bullet();

		void update();

		unsigned int getLifetime();
		void setLifetime(unsigned int);

};

#endif
