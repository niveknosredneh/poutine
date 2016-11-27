#ifndef WALL_H
#define WALL_H

extern int wallBuffer;


class Wall
{

	protected:

        SDL_Rect wallRect;

		int Xposition; //top left coordinate of rectangle
		int Yposition;

		int Height;
		int Width;

		int wallBuffer;

		int RED;
		int BLUE;
		int GREEN;

		bool isVertical;


	public:

		//Initializes variables
		Wall(int,int,int,bool);

		//Deallocates memory
		~Wall();

		void getRect(SDL_Rect&);
		
		bool getVertical();

		void render(int camX, int camY);

};



#endif
