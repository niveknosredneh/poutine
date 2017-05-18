#include "main.h"
#include "sprite.h"


extern std::vector<Sprite> planets;
extern Timer fpsTimer;

extern TTF_Font* gFont16;
extern TTF_Font* gFont12;

extern SDL_Color white,cyan;
extern SDL_Rect camera;


extern SDL_Renderer* gRenderer;

// default no arguments
Sprite::Sprite()
{
    Width.x = 25;
    Width.y = 25;
	Depth = 1; // default
	Period = 0; // means not rotating
	Mass = 100; //

    Position.x = SCREEN_WIDTH/2;
    Position.y = SCREEN_HEIGHT/2;

	// change in position per tick (px/tick)
    setVelocity({0,0});
	maxVelocity = 25;

    setAcceleration({0,0});
	maxAcceleration = 10;

    Colour = cyan;
    label = "null";
	collisionFlag = false;

}

Sprite::Sprite(int diameter, int mass, SDL_Color nColour, double radius, int period, bool clockwise, std::vector<Sprite>::size_type rotationPlanet, std::string name )
{
    Position.x = rand() % LEVEL_WIDTH; // dont think this matters, update puts them into orbit after first tick
    Position.y = rand() % LEVEL_HEIGHT;
    Width.x = diameter;
    Width.y = diameter;
    Colour = nColour;
    label = name;
    Radius = radius;
    Depth = 1; // default
    Period = period;
    Mass = mass;

    isClockwise = clockwise;

    RotatingAround = rotationPlanet;

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
        // off screen conditions
        if(Position.x<0)
            Position.x=Width.x*3;
        if(Position.x>LEVEL_WIDTH-Width.x)
            Position.x=LEVEL_WIDTH-Width.x*3;
        if(Position.y<0)
            Position.y=Width.y*3;
        if(Position.y>LEVEL_HEIGHT-Width.y)
            Position.y=LEVEL_HEIGHT-Width.y*3;

        if(Period==0) // means not orbiting around anything
        {
            setVelocity( {Velocity.x+Acceleration.x,Velocity.y+Acceleration.y} ); // use method to cap velocity
            Position.x += Velocity.x; Position.y += Velocity.y;


        }
        else // means anything with an orbit
        {
            Position = changeAngle(planets[RotatingAround].getPosition(),Position, Radius, 10.f/ Period);

        }

}

// used to render all sprites
void Sprite::render(double zoomX, bool follows, bool printLabel, int xOffset, int yOffset)
{
    SDL_SetRenderDrawColor( gRenderer, Colour.r, Colour.g, Colour.b, 0xFF );

    double zoomY;
    if(zoomX==1) zoomY = 1;
    else zoomY = zoomX*miniDivY/miniDivX;
    int followsCam = follows;

    if(Width.x*0.5/zoomX<=1)
    {
        SDL_RenderDrawPoint(gRenderer, ( (Position.x - ( camera.x * followsCam / Depth)) / zoomX) + xOffset, ( (Position.y - ( camera.y * followsCam  / Depth)) / zoomY) + yOffset);
    }
    else filledCircleColor(gRenderer, ( (Position.x  - ( camera.x * followsCam  / Depth)) / zoomX) + xOffset, ( (Position.y - ( camera.y * followsCam  / Depth)) / zoomY) + yOffset, (Width.x*0.5/zoomX), ((0xff) << 24) + ((Colour.b & 0xff) << 16) + ((Colour.g & 0xff) << 8) + (Colour.r & 0xff));
}






bool Sprite::checkCollision(SDL_Rect* rect)
{


}


void Sprite::collisionResponse(SDL_Rect newRect)
{
    // revamp collision!!! maybe some circle detection


}

void Sprite::setCollision()
{
    collisionFlag = true;
}

void Sprite::bePulled(Sprite S1, int force)
{
    if(force>0)
    {
        double Theta = getTheta(Position,S1.getPosition());
        int Xchange = force * std::cos(Theta);
        int Ychange = force * std::sin(Theta);

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderDrawLine(gRenderer,Position.x-camera.x,Position.y-camera.y,Position.x+Xchange*15-camera.x,Position.y+Ychange*15 -camera.y);
        gTextTexture.loadFromRenderedText(std::to_string( (int)getRadius(Position,S1.getPosition())/10 ) + " - " + S1.getlabel(), gFont12, white );
        gTextTexture.render( Position.x+Xchange*15-camera.x, Position.y+Ychange*15 -camera.y);

        Position = {Position.x+Xchange, Position.y+Ychange};
    }

}


double Sprite::getRad() { return Radius; }

double Sprite::getAngle() { return Angle; }

void Sprite::setAngle(double newAngle) { Angle = newAngle; }

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
std::string Sprite::getlabel() { return label; }
