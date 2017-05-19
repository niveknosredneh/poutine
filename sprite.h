#ifndef SPRITE_H
#define SPRITE_H

class Bullet;

class Sprite
{
	protected:

		SDL_Point Width;
		int Depth;  // used for camera multiplier (stars)

		int Mass; // TODO

		std::vector<Sprite>::size_type RotatingAround;
		int Period;
        double Radius;
        double Angle;
        bool isClockwise;

		SDL_Colour Colour;

		SDL_Point Position;
		SDL_Point Velocity;
		int maxVelocity;
		SDL_Point Acceleration;
		int maxAcceleration;

		bool collisionFlag;

		std::string label;


	public:
		//Initializes variables
		Sprite();
		Sprite(int W, int mass, SDL_Color, double radius, int period, bool, std::vector<Sprite>::size_type, std::string );

		//Deallocates memory
		~Sprite();

		void update();

		void render(double,bool,bool,int,int);
		void renderLabel(double, TTF_Font* font,SDL_Colour);
        void renderLabel(double, TTF_Font* font);

		bool checkCollision(SDL_Rect*);
		void collisionResponse(SDL_Rect);
		SDL_Rect getCollision(SDL_Rect*);
		void unsetCollision();
		void setCollision();

		void bePulled(Sprite S1, int force);

		SDL_Rect getRect();
		SDL_Rect getLastRect();

		double getRad();
		std::vector<Sprite>::size_type getRotating();
		int getPeriod();

		SDL_Point getWidth();
		void setWidth(SDL_Point);

		int getDepth();
        void setDepth(int newDepth);

        double getAngle();
        void setAngle(double);

        SDL_Point getCentre();

        SDL_Colour getColour();
		void setColour(SDL_Colour);

		SDL_Point getPosition();
		void setPosition(SDL_Point);

		SDL_Point getVelocity();
		void setVelocity(SDL_Point);
        void setMaxVelocity(int);

		SDL_Point getAcceleration();
		void setAcceleration(SDL_Point);

		void invertXvelocity();
		void invertYvelocity();

		int getMass();
		std::string getlabel();
};

#endif
