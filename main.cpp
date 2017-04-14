
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

const int LEVEL_WIDTH = 20000;
const int LEVEL_HEIGHT = 20000;

const int CAPPED_FPS = 15;
const int TICKS_PER_FRAME = 1000 / CAPPED_FPS;

SDL_Color red   = {108, 26, 9};
SDL_Color green = {0,255,0};
SDL_Color blue  = {32, 111, 176};
SDL_Color lightblue  = {113, 187, 249};
SDL_Color white = {255,255,255};
SDL_Color darkgray = {69,69,69};
SDL_Color orange = {221, 131, 16};
SDL_Color darkorange = {166, 115, 4};
SDL_Color yellow   = {255,255,0};
SDL_Color cyan   = {0,255,255};
SDL_Color magenta   = {255,0,255};
SDL_Color brown   = {109, 54, 43};

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


        // begin Planet definitions
        std::vector<Sprite> planets;

        Sprite sol(5000,5000, 7000, 7000, yellow, 0, 0, "sol");
        planets.push_back(sol);
        sprites.push_back(sol); // add to list of sprites

        Sprite mercury(500,700, 25, 25, white, 4000, 0,"mercury");
        planets.push_back(mercury);
        sprites.push_back(mercury);

        Sprite venus(500,700, 80, 80, orange, 5000, 0,"venus");
        planets.push_back(venus);
        sprites.push_back(venus);

        Sprite terra(500,700, 70, 70, blue, 6600, 0,"terra");
        planets.push_back(terra);
        sprites.push_back(terra);

        Sprite luna(500,700, 8, 8, yellow, 100, 3,"luna");
        planets.push_back(luna);
        sprites.push_back(luna);

        Sprite mars(600,600, 90, 90, red, 8000, 0,"mars");
        planets.push_back(mars);
        sprites.push_back(mars);

        Sprite phobos(500,500, 30, 30, darkorange, 150, 5,"phobos");
        planets.push_back(phobos);
        sprites.push_back(phobos);

        Sprite deimos(500,700, 20, 20, red, 250, 5,"deimos");
        planets.push_back(deimos);
        sprites.push_back(deimos);

        Sprite jupitor(500,700, 20, 20, brown, 10000, 0,"jupitor");
        planets.push_back(jupitor);
        sprites.push_back(jupitor);

        Sprite saturn(500,700, 20, 20, red, 11000, 0,"saturn");
        planets.push_back(saturn);
        sprites.push_back(saturn);

        Sprite uranus(500,700, 20, 20, lightblue, 12000, 0,"uranus");
        planets.push_back(uranus);
        sprites.push_back(uranus);

        Sprite neptune(500,700, 20, 20, blue, 13500, 0,"neptune");
        planets.push_back(neptune);
        sprites.push_back(neptune);





        // end planet definitions


        std::vector<Sprite> stars1;
        for(int i = 0; i<6000; i++)
        {
                    //// find better divider const than 4
            Sprite newstar(rand() % (LEVEL_WIDTH/10), rand() % LEVEL_HEIGHT/10, 1, 1, {(rand() % 100)+155,(rand() % 100)+155,0}, 0, 0, "null");
            newstar.setDepth((rand() % 30) + 10 );
            stars1.push_back(newstar);
        }

        std::vector<Sprite> asteroids1;
        for(int i = 0; i<7; i++)
        {
            Sprite newast(0,0, 10, 10, blue, 400, 0, std::to_string(i));
            asteroids1.push_back(newast);
        }




        // timer init
        Timer fpsTimer; // Timer object
        Timer capTimer;
        std::stringstream timeText; //In memory text stream
		fpsTimer.start(); //Start counting frames per second
		int countedFrames = 0;
		// end timer init

		//The camera area
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };



		std::thread t1(networkLoop);

        bool quit = false; //Main loop flag
		while( !quit ) 	// MAIN LOOP STARTS HERE
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


                // renders all stars
                for (std::vector<Sprite>::size_type i = 0; i < stars1.size(); i++) stars1[i].render(camera.x,camera.y);

                // renders all stars
                for (std::vector<Sprite>::size_type i = 0; i < asteroids1.size(); i++) asteroids1[i].render(camera.x,camera.y);

                //update sprites
                hero1.update();
                hero1.updateCompanions();


                for (std::vector<Sprite>::size_type i = 0; i < planets.size(); i++)
                {
                    planets[i].update();

                    // just for fun ... planet lines
                    SDL_SetRenderDrawColor(gRenderer, planets[i].getRED(), planets[i].getGREEN(), planets[i].getBLUE(), SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(gRenderer, planets[planets[i].getRotating()].getXposition()+planets[planets[i].getRotating()].getWidth()/2 - camera.x, planets[planets[i].getRotating()].getYposition()+planets[planets[i].getRotating()].getHeight()/2 - camera.y,
                                        planets[i].getXposition()+planets[i].getWidth()/2 - camera.x, planets[i].getYposition()+planets[i].getHeight()/2 - camera.y );
                    // end planet lines

                    SDL_Rect newRect;
                    if(i!=0)
                    {
                        newRect = changeAngle(planets[planets[i].getRotating()],planets[i], 0.2) ;

                        planets[i].setXposition(newRect.x);
                        planets[i].setYposition(newRect.y);

                    }


                    newRect = planets[i].getRect();
                    if (hero1.checkCollision(&newRect))
                    {
                        //planets[i].ifCollision();
                        hero1.collisionResponse(newRect);


                        filledCircleColor(gRenderer, hero1.getXposition() + hero1.getWidth()/2 - camera.x, hero1.getYposition() + hero1.getHeight()/2 - camera.y , 13, 0xFF0000FF);
                    }
                }

                for (std::vector<Sprite>::size_type i = 0; i < asteroids1.size(); i++)
                {
                    asteroids1[i].update();

                    // just for fun ... planet lines
                    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(gRenderer, planets[planets[i].getRotating()].getXposition()+planets[planets[i].getRotating()].getWidth()/2 - camera.x, planets[planets[i].getRotating()].getYposition()+planets[planets[i].getRotating()].getHeight()/2 - camera.y,
                                        planets[i].getXposition()+planets[i].getWidth()/2 - camera.x, planets[i].getYposition()+planets[i].getHeight()/2 - camera.y );
                    // end planet lines

                    SDL_Rect newRect;
                    if(i!=0)
                    {
                        newRect = changeAngle(planets[asteroids1[i].getRotating()],asteroids1[i], 0.5* i);

                        asteroids1[i].setXposition(newRect.x);
                        asteroids1[i].setYposition(newRect.y);

                    }

                }






                // render sprites after collision detection
                for (std::vector<Sprite>::size_type i = 0; i < planets.size(); i++)
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

            gTextTexture.loadFromRenderedText( std::to_string( getRadius(hero1,planets[0])), gFont12,  red );
            gTextTexture.render( 10, 40 );

            double theta = getTheta(hero1,planets[0]) * 180.0/3.141593;;
            if (theta<0) theta+=360; // weird degree conversion, cant explain

            gTextTexture.loadFromRenderedText( std::to_string(theta), gFont12,  red );
            gTextTexture.render( 10, 55 );
            gTextTexture.loadFromRenderedText( std::to_string(hero1.getXposition()) + ", "
                                            + std::to_string(hero1.getXvelocity()) + " / "
                                            + std::to_string(hero1.getYposition()) + ", "
                                            + std::to_string(hero1.getYvelocity())
                                            , gFont12,  red );
            gTextTexture.render( 10, 70 );
            gTextTexture.loadFromRenderedText( std::to_string(sprites.size()), gFont12,  red );
            gTextTexture.render( 10, 85 );

            // END DEBUG HUD section --->


            //Update screen - only need to do this once per frame
            SDL_RenderPresent( gRenderer );


		}  // END MAIN LOOP HERE
	}

	close(); //Free resources and close SDL
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
