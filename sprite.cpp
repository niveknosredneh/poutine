#include "main.h"
#include "sprite.h"

extern TTF_Font* gFont16;
extern TTF_Font* gFont12;

extern SDL_Color white;
extern SDL_Rect camera;


extern SDL_Renderer* gRenderer;

// default no arguments
Sprite::Sprite()
{
    Width.x = 10;
    Width.y = 10;
	Depth = 1; // default
	Period=0; // means not rotating
	Mass = 1; // TODO

    Position.x = SCREEN_WIDTH/2.3;
    Position.y = SCREEN_HEIGHT/2.3;

	// change in position per tick (px/tick)
    setVelocity({0,0});
	maxVelocity = 15;

    setAcceleration({0,0});
	maxAcceleration = 10;

	SpRect = {Position.x,Position.y, Width.x, Width.y};

    Colour = {0,0,0};
    label = "null";
	collisionFlag = false;

}

Sprite::Sprite(int X, int Y, SDL_Color nColour, double radius, int period, bool clockwise, std::vector<Sprite>::size_type rotationPlanet, std::string name )
{
    Position.x = rand() % LEVEL_WIDTH; // dont think this matters, update puts them into orbit after first tick
    Position.y = rand() % LEVEL_HEIGHT;
    Width.x = X;
    Width.y = Y;
    Colour = nColour;
    label = name;
    Radius = radius;
    Depth = 1; // default
    Period = period;

    isClockwise = clockwise;

    RotatingAround = rotationPlanet;

    SpRect = {Position.x,Position.y, Width.x, Width.x};

    setVelocity({0,0});
    maxVelocity = 10;

    setAcceleration({0,0});
	maxAcceleration = 10;

}

Sprite::~Sprite()
{
	// TODO learn how to clean up properly
}


// updates position on screen and does some other stuff
void Sprite::update()
{

        lastRect = { Position.x, Position.y, Width.x, Width.y };

        // off screen conditions
        if(Position.x<0)
            Position.x=Width.x*3;
        if(Position.x>LEVEL_WIDTH-Width.x)
            Position.x=LEVEL_WIDTH-Width.x*3;
        if(Position.y<0)
            Position.y=Width.y*3;
        if(Position.y>LEVEL_HEIGHT-Width.y)
            Position.y=LEVEL_HEIGHT-Width.y*3;

        setVelocity({Velocity.x+Acceleration.x,Velocity.y+Acceleration.y} );

        Position.x += Velocity.x;
        Position.y += Velocity.y;

        SpRect = { Position.x, Position.y, Width.x, Width.y };

        unsetCollision();

}

void Sprite::render(int camx, int camy)
{

        double miniDivX = LEVEL_WIDTH/SCREEN_WIDTH;
        double miniDivY = LEVEL_HEIGHT/SCREEN_HEIGHT;

		// render sprite
        SDL_Rect SpRect = { Position.x - ( camx / Depth), Position.y - ( camy / Depth), Width.x, Width.y };

		SDL_SetRenderDrawColor( gRenderer, Colour.r, Colour.g, Colour.b, 0xFF );
		if(Width.x==1&&mainState!=MAIN_MENU) SDL_RenderFillRect( gRenderer, &SpRect ); // for stars

        // if main menu, make map, else render normally
        else if(mainState==MAIN_MENU && Width.y/miniDivY<1) filledCircleColor(gRenderer, (getCentre().x)/miniDivX, (getCentre().y)/miniDivY , 1, ((0xff) << 24) + ((Colour.b & 0xff) << 16) + ((Colour.g & 0xff) << 8) + (Colour.r & 0xff));
		else if(mainState==MAIN_MENU) filledCircleColor(gRenderer, (getCentre().x)/miniDivX, (getCentre().y)/miniDivY , (Width.x*9/14)/ miniDivY, ((0xff) << 24) + ((Colour.b & 0xff) << 16) + ((Colour.g & 0xff) << 8) + (Colour.r & 0xff));
        // finally, if not in mini map mode:
        else if(mainState!=MAIN_MENU && (Position.x-camx) < SCREEN_WIDTH && (Position.x-camx) > 0 && (Position.y-camy) < SCREEN_HEIGHT && (Position.y-camy))
            filledCircleColor(gRenderer, getCentre().x - camx, getCentre().y - camy , Width.y*9/14, ((0xff) << 24) + ((Colour.b & 0xff) << 16) + ((Colour.g & 0xff) << 8) + (Colour.r & 0xff));

        if(label=="saturn") // rings of saturn
        {
            for(int i = 0; i<12; i++) ellipseRGBA(gRenderer, Position.x + Width.x/2 - camx ,Position.y + Width.y/2 - 70 - 3.5*i -  camy , Width.x + 15*i, Width.y - 400 + 15*i, 255,0,35*i,3*i );
        }

        // trying to do in game mini map
        if(mainState==LEVEL1 && Width.y/(miniDivY*6)<1) SDL_RenderDrawPoint(gRenderer, ((getCentre().x)/miniDivX)/6 + 1600, ((getCentre().y)/miniDivY)/6 );
        else if(mainState==LEVEL1) filledCircleColor(gRenderer, ((getCentre().x)/miniDivX)/6 + 1600, ((getCentre().y)/miniDivY)/6 , ((Width.y*9/14)/ miniDivY*1.18)/6, ((0xff) << 24) + ((Colour.b & 0xff) << 16) + ((Colour.g & 0xff) << 8) + (Colour.r & 0xff));

		if(label!="null")
		{
            gTextTexture.loadFromRenderedText(label, gFont12, white );
            if(mainState==MAIN_MENU && RotatingAround==0) gTextTexture.render( getCentre().x / miniDivX, Position.y / miniDivY);
            else if (mainState == LEVEL1) gTextTexture.render( getCentre().x - sizeof(label) - camx, Position.y - 15 - camy - 15);
		}

}


bool Sprite::checkCollision(SDL_Rect* rect)
{

    bool flag = false;
    if ( SDL_HasIntersection(&SpRect,rect)==SDL_TRUE )
	{
		flag = true;
		collisionFlag = true;
    }

	return flag;
}


void Sprite::collisionResponse(SDL_Rect newRect)
{
    SDL_Rect collisionRect = getCollision(&newRect);

	// revamp collision!!! maybe some circle detection


}

void Sprite::setCollision()
{
    collisionFlag = true;
}
SDL_Rect Sprite::getCollision(SDL_Rect* rect)
{
    SDL_Rect result;
    SDL_IntersectRect(&SpRect,rect,&result);
    return result;
}


SDL_Rect Sprite::getRect()
{
    SpRect = {Position.x,Position.y, Width.x, Width.y};
    return SpRect;
}

double Sprite::getRad() { return Radius; }

double Sprite::getAngle() { return Angle; }

void Sprite::setAngle(double newAngle) { Angle = newAngle; }

SDL_Point Sprite::getCentre() { return { Position.x+Width.x/2,Position.y+Width.y/2 }; }

SDL_Rect Sprite::getLastRect() { return lastRect; }

SDL_Point Sprite::getVelocity() { return Velocity; }

void Sprite::setVelocity(SDL_Point amount)
{
    int newX,newY;
	if(amount.x > maxVelocity)
		newX = maxVelocity;
	else if(amount.x < -maxVelocity)
		newX = -maxVelocity;
	else
		newX = amount.x;
    if(amount.y > maxVelocity)
		newY = maxVelocity;
	else if(amount.y < -maxVelocity)
		newY = -maxVelocity;
	else
		newY = amount.y;

    Velocity = {newX,newY};
}

void Sprite::setMaxVelocity(int value) { maxVelocity = value; }

SDL_Point Sprite::getAcceleration() { return Acceleration; }
void Sprite::setAcceleration(SDL_Point newAccel) { Acceleration = newAccel; }

void Sprite::invertXvelocity() { Velocity.x *= -1; }

void Sprite::invertYvelocity() { Velocity.y *= -1; }

std::vector<Sprite>::size_type Sprite::getRotating() { return RotatingAround; }

int Sprite::getPeriod() { return Period; }

SDL_Point Sprite::getWidth() { return Width; }
void Sprite::setWidth(SDL_Point newWidth) {Width.x = newWidth.x; Width.y = newWidth.y; }

int Sprite::getDepth() {	return Depth; }
void Sprite::setDepth(int newDepth){ Depth = newDepth; }

SDL_Point Sprite::getPosition() { return Position; }
void Sprite::setPosition(SDL_Point newPos) { Position = newPos; }

SDL_Colour Sprite::getColour() { return Colour; }
void Sprite::setColour(SDL_Colour newColour) { Colour = newColour; }

void Sprite::unsetCollision() { collisionFlag = false; }

int Sprite::getMass() { return Mass; }
