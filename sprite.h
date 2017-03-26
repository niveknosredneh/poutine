#ifndef SPRITE_H
#define SPRITE_H

class Bullet;

class Sprite
{
	protected:

        SDL_Rect lastRect;
        SDL_Rect SpriteRect;

		//Image dimensions
		int Height;
		int Width;

		int Mass; // TODO

		int Xposition; //top left coordinate of rectangle
		int Yposition;

		int RED;
		int BLUE;
		int GREEN;

		int Xvelocity;
		int Yvelocity;
		int maxVelocity;

		int Xacceleration;
		int Yacceleration;
		int maxAcceleration;

		bool collisionFlag;

	public:
		//Initializes variables
		Sprite();

		//Deallocates memory
		~Sprite();

		void update();

		void render(int,int);

		bool checkCollision(SDL_Rect*);
		void collisionResponse(SDL_Rect);
		SDL_Rect getCollision(SDL_Rect*);
		void unsetCollision();
		void setCollision();

		SDL_Rect getRect();
		SDL_Rect getLastRect();

		void spawn (int,int);

		void setMaxVelocity(int);

		//Gets image dimensions
		int getWidth();
		int getHeight();
		void setHeight(int newHeight);
		void setWidth(int newWidth);

		//Gets image dimensions
		int getXposition();
		int getYposition();

        void setXposition(int);
		void setYposition(int);		//Gets image dimensions

		int getRED();
		int getGREEN();
		int getBLUE();

		void setRED(int newRED);
		void setGREEN(int newGREEN);
		void setBLUE(int newBLUE);

		int getXvelocity();
		int getYvelocity();

		void setXvelocity(int amount);
        void setYvelocity(int amount);

		int getXacceleration();
		int getYacceleration();

		void setXacceleration(int);
		void setYacceleration(int);

		void invertXvelocity();
		void invertYvelocity();

		int getMass();
};

#endif
