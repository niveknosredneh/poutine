
#include "main.h"

Hero hero1;

GameState mainState = MAIN_MENU; // see main.h
short menuSelector = 0;

std::string DMSG;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1024;

const int LEVEL_WIDTH = 10000;
const int LEVEL_HEIGHT = 10000;

const int CAPPED_FPS = 25;
const int TICKS_PER_FRAME = 1000 / CAPPED_FPS;

SDL_Color red   = {255,0,0};
SDL_Color green = {0,255,0};
SDL_Color blue  = {0,0,255};
SDL_Color white = {255,255,255};
SDL_Color darkgray = {69,69,69};
SDL_Color yellow   = {255,255,0};
SDL_Color cyan   = {0,255,255};
SDL_Color magenta   = {255,0,255};

Menu mainMenu;

//Globally used font
TTF_Font *gFont24 = NULL;
TTF_Font *gFont16 = NULL;
TTF_Font *gFont12 = NULL;

//Rendered texture
Texture gTextTexture;

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() ) {	printf( "Failed to initialize!" ); }
	else // SDL has started succesfully
	{

		SDL_Event e; //Event handler

        loadMedia();

        //audioToggleBG();

		std::vector<Sprite> sprites; // master list of sprites ? (not subsprites)
		sprites.push_back(hero1);

        std::vector<Planet> planets;

        for (int i = 0; i < 3; i++)
        {
            Planet newPlanet(i);
            planets.push_back(newPlanet);
            sprites.push_back(newPlanet); // add to list of sprites

        }


        Timer fpsTimer; // Timer object
        Timer capTimer;
        std::stringstream timeText; //In memory text stream

        //Start counting frames per second
		fpsTimer.start();
		int countedFrames = 0;

		//The camera area
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

		bool quit = false; //Main loop flag

		std::thread t1(networkLoop);

		while( !quit ) 	// Main game loop
		{

            //Start cap timer
            capTimer.start();

            //Calculate fps
            float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );

            //convert fps number to text
            timeText.str( "" );
            timeText << "FPS " << avgFPS;

            //clear the screen
            SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
            SDL_RenderClear( gRenderer );

            if(mainState==QUIT)
            {
                quit=true;
            }

            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
            }

            bool status = eventHandler(); // handle user input

		    if(mainState == MAIN_MENU)
            {

                mainMenu.render();

                SDL_Delay(80);

            }

            if(mainState == OPTIONS)
            {
                //havent gotten this far
                mainState = MAIN_MENU;
            }

            if(mainState == OPTIONS)
            {
                //havent gotten this far
                mainState = MAIN_MENU;
            }

            if(mainState == MULTIPLAYER)
            {

                //havent gotten this far
                mainState = MAIN_MENU;

            }


            if(mainState == LEVEL1)
            {


                // where to place vision
                camera.x =  hero1.getXposition() - SCREEN_WIDTH/2;
                camera.y =  hero1.getYposition() - SCREEN_HEIGHT/2;


                //Keep the camera in bounds
                if( camera.x < 0 )
                {
                    camera.x = 0;
                }
                if( camera.y < 0 )
                {
                    camera.y = 0;
                }
                if( camera.x > LEVEL_WIDTH - camera.w )
                {
                    camera.x = LEVEL_WIDTH - camera.w;
                }
                if( camera.y > LEVEL_HEIGHT - camera.h )
                {
                    camera.y = LEVEL_HEIGHT - camera.h;
                }

                //update sprites
                hero1.update();
                hero1.updateCompanions();





                SDL_Rect newRect = changeAngle(planets[0].getRect(),planets[1].getRect(), 5);
                planets[1].setXposition(newRect.x);
                planets[1].setYposition(newRect.y);
                newRect = changeAngle(planets[0].getRect(),planets[2].getRect(), 5);
                planets[2].setXposition(newRect.x);
                planets[2].setYposition(newRect.y);


                for (std::vector<Planet>::size_type i = 0; i < planets.size(); i++)
                {
                    planets[i].update();

                    // just for fun ... planet lines
                    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(gRenderer, hero1.getXposition()+hero1.getWidth()/2 - camera.x, hero1.getYposition()+hero1.getHeight()/2 - camera.y,
                                        planets[i].getXposition()+planets[i].getWidth()/2 - camera.x, planets[i].getYposition()+planets[i].getHeight()/2 - camera.y );
                    // end planet lines


                    SDL_Rect newRect = planets[i].getRect();
                    if (hero1.checkCollision(&newRect))
                    {
                        planets[i].ifCollision();
                        hero1.collisionResponse(newRect);


                        filledCircleColor(gRenderer, hero1.getXposition() + hero1.getWidth()/2 - camera.x, hero1.getYposition() + hero1.getHeight()/2 - camera.y , 13, 0xFF0000FF);
                    }
                }






                // render sprites after collision detection
                for (std::vector<Planet>::size_type i = 0; i < planets.size(); i++)
                {
                    planets[i].render(camera.x,camera.y);
                }


                hero1.Sprite::render(camera.x, camera.y);
                hero1.Hero::renderBullets(camera.x,camera.y);

            }


            // FPS limiter
            // If frame finished early
            ++countedFrames;
            int frameTicks = capTimer.getTicks();
            if( frameTicks < TICKS_PER_FRAME )
            {
                SDL_Delay( TICKS_PER_FRAME - frameTicks );
            }


            std::string debug = (std::string)SDL_GetPlatform() + " "
                                + std::to_string(SDL_GetCPUCount()) + "xCPU "
                                + std::to_string(SDL_GetSystemRAM()) + "MB RAM";


            // <---- DEBUG HUD
            // takes FPS from capTimer which gets reset each frame, not averaged out
            gTextTexture.loadFromRenderedText( debug, gFont12,  red );
            gTextTexture.render( 10, 10 );

            gTextTexture.loadFromRenderedText( std::to_string(1000.f / capTimer.getTicks()) + " fps" , gFont12,  red );
            gTextTexture.render( 10, 25 );

            gTextTexture.loadFromRenderedText( std::to_string( getRadius(hero1.getRect(),planets[0].getRect())), gFont12,  red );
            gTextTexture.render( 10, 40 );

            double theta = getTheta(hero1.getRect(),planets[0].getRect()) * 180.0/3.141593;;
            if (theta<0) theta+=360; // weird degree conversion, cant explain

            gTextTexture.loadFromRenderedText( std::to_string(theta), gFont12,  red );
            gTextTexture.render( 10, 55 );
            gTextTexture.loadFromRenderedText( std::to_string(hero1.getXposition()) + ", "
                                            + std::to_string(hero1.getXvelocity()) + " / "
                                            + std::to_string(hero1.getYposition()) + ", "
                                            + std::to_string(hero1.getYvelocity())
                                            , gFont12,  red );
            gTextTexture.render( 10, 70 );
            gTextTexture.loadFromRenderedText( DMSG, gFont12,  red );
            gTextTexture.render( 10, 85 );

            // END DEBUG HUD section --->


            //Update screen - only need to do this once per frame
            SDL_RenderPresent( gRenderer );


		}  // end of main loop
	}

	//Free resources and close SDL
	close();

	return 0;
}

void menuSelect(int change)
{
    if(change==-1)
    {
        if(menuSelector==0) menuSelector=3;
        else menuSelector+=change;
    }
    else if(change==1)
    {
        if(menuSelector==3) menuSelector=0;
        else menuSelector+=change;
    }

}
