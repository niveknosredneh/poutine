
#include "main.h"

Hero hero1;

GameState mainState = MAIN_MENU; // see main.h
short menuSelector = 0;


bool isDebug = true;
std::string DMSG;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int LEVEL_WIDTH = 500000;
const int LEVEL_HEIGHT = 500000;

//The camera area
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

const int CAPPED_FPS = 30;
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

        Sprite sol(7000, 7000, yellow, 0, 0, 0, "null"); // we all get that its the sun, no label
        sol.setXposition(LEVEL_WIDTH/2 - sol.getWidth()/2);
        sol.setYposition(LEVEL_HEIGHT/2 - sol.getHeight()/2);
        planets.push_back(sol);
        sprites.push_back(sol); // add to list of sprites

        Sprite mercury(24, 24, white, 6000, 40 ,0 ,"mercury");
        planets.push_back(mercury);
        sprites.push_back(mercury);

        Sprite venus(60, 60, orange, 8500, 62,  0,"venus");
        planets.push_back(venus);
        sprites.push_back(venus);

        Sprite terra(63, 63, blue, 11000, 100, 0,"terra");
        planets.push_back(terra);
        sprites.push_back(terra);

        Sprite luna(17, 17, brown, 450, 3, 3,"luna");
        planets.push_back(luna);
        sprites.push_back(luna);

        Sprite mars(33, 33, red, 14000, 188, 0,"mars");
        planets.push_back(mars);
        sprites.push_back(mars);

        Sprite phobos(3, 3, darkorange, 200, 2, 5,"phobos");
        planets.push_back(phobos);
        sprites.push_back(phobos);

        Sprite deimos(2, 2, red, 450, 4, 5,"deimos");
        planets.push_back(deimos);
        sprites.push_back(deimos);

        Sprite ceres(20, 20, darkorange, 22050, 459, 0,"ceres");
        planets.push_back(ceres);
        sprites.push_back(ceres);

        Sprite jupiter(700, 700, brown, 30000, 1200, 0,"jupiter");
        planets.push_back(jupiter);
        sprites.push_back(jupiter);

        Sprite ganymede(10, 10, brown, 1100, 20, 9,"ganymede");
        planets.push_back(ganymede);
        sprites.push_back(ganymede);

        Sprite europa(10, 10, brown, 1000, 10, 9,"europa");
        planets.push_back(europa);
        sprites.push_back(europa);

        Sprite callisto(10, 10, brown, 1200, 40,  9,"callisto");
        planets.push_back(callisto);
        sprites.push_back(callisto);

        Sprite io(10, 10, brown, 900, 3, 9,"io");
        planets.push_back(io);
        sprites.push_back(io);

        Sprite saturn(580, 580, red, 55000, 2946, 0,"saturn");
        planets.push_back(saturn);
        sprites.push_back(saturn);

        Sprite titan(10, 10, yellow, 1000, 8, 14,"titan");
        planets.push_back(titan);
        sprites.push_back(titan);

        Sprite uranus(250, 250, lightblue, 80000, 8400, 0,"uranus");
        planets.push_back(uranus);
        sprites.push_back(uranus);

        Sprite neptune(240, 240, blue, 110000, 16480, 0,"neptune");
        planets.push_back(neptune);
        sprites.push_back(neptune);

        Sprite triton(13, 13, blue, 500, 67000, 17,"triton");
        planets.push_back(triton);
        sprites.push_back(triton);

        // end planet definitions


        std::vector<Sprite> stars1; // not added to master list of sprites
        for(int i = 0; i<5000; i++)
        {
            //// find better divider const than 10
            Sprite newstar;
            newstar.setXposition(rand() % LEVEL_WIDTH/10);
            newstar.setYposition(rand() % LEVEL_HEIGHT/10);
            newstar.setWidth(1);
            newstar.setHeight(1);
            newstar.setRED((rand() % 100)+155);
            newstar.setGREEN((rand() % 100)+155);
            newstar.setDepth((rand() % 30) + 10 );
            stars1.push_back(newstar);
        }

        //inner belt
        std::vector<Sprite> asteroids1;
        for(int i = 0; i<2000; i++)
        {
            int diam = (rand() % 5) + 5;
            Sprite newast(diam, diam, blue, 22000 + (rand() % 800), 1000 + rand() % 300 , 0, "null");
            asteroids1.push_back(newast);
            sprites.push_back(newast);
        }

        // timer init
        Timer fpsTimer, capTimer; // Timer object
		fpsTimer.start(); //Start counting frames per second
		int countedFrames = 0;
		// end timer init



        // disable networking
		//std::thread t1(networkLoop);

        bool quit = false; //Main loop flag
		while( !quit ) 	// MAIN LOOP STARTS HERE
		{
            capTimer.start(); //Start cap timer

            //clear the screen
            SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
            SDL_RenderClear( gRenderer );

            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 ) if( e.type == SDL_QUIT ) quit = true;
            bool status = eventHandler(); // handle user input

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

            if(mainState==LEVEL1) // renders stars and minimap for gameplay
            {
                // renders all stars
                for (std::vector<Sprite>::size_type i = 0; i < stars1.size(); i++) stars1[i].render(camera.x,camera.y);

                SDL_SetRenderDrawColor( gRenderer, 0XFF, 0XFF, 0XFF, 0xFF );
                SDL_Rect newRect = {5*SCREEN_WIDTH/6 - 2,0, SCREEN_WIDTH/6 + 4, SCREEN_HEIGHT/6 + 4};
                SDL_RenderFillRect( gRenderer, &newRect );
                SDL_SetRenderDrawColor( gRenderer, 0X00, 0X00, 0X00, 0xFF );
                newRect = {5*SCREEN_WIDTH/6, 2, SCREEN_WIDTH/6 - 2, SCREEN_HEIGHT/6};
                SDL_RenderFillRect( gRenderer, &newRect ); // render over stars fo mini map


            }

            // renders all asteroids
            for (std::vector<Sprite>::size_type i = 0; i < asteroids1.size(); i++)
            {
                    asteroids1[i].update();

                    SDL_Rect newRect;
                    newRect = changeAngle(planets[asteroids1[i].getRotating()],asteroids1[i], 10.f/ asteroids1[i].getPeriod());

                    asteroids1[i].setXposition(newRect.x);
                    asteroids1[i].setYposition(newRect.y);

                    asteroids1[i].render(camera.x,camera.y);
            }

            for (std::vector<Sprite>::size_type i = 0; i < planets.size(); i++)
            {
                planets[i].update();

                SDL_Rect newRect;
                if(i!=0)
                {
                    if(planets[i].getRotating()==0 ) newRect = changeAngle(planets[planets[i].getRotating()],planets[i], 10.f/ planets[i].getPeriod() ) ;
                    else newRect = changeAngle(planets[planets[i].getRotating()],planets[i], 10.f/ planets[i].getPeriod()) ;

                    planets[i].setXposition(newRect.x);
                    planets[i].setYposition(newRect.y);

                }

                planets[i].render(camera.x,camera.y);

                newRect = planets[i].getRect();
                if (hero1.checkCollision(&newRect))
                {
                    //planets[i].ifCollision();
                    hero1.collisionResponse(newRect);

                    circleColor(gRenderer, hero1.getXposition() + hero1.getWidth()/2 - camera.x, hero1.getYposition() + hero1.getHeight()/2 - camera.y , 13, 0xFF0000FF);
                }
            }


            // !! everything before this point inside the main loop gets executed regardless of game state !!


            if(mainState==QUIT)
            {
                quit=true;
            }

		    if(mainState == MAIN_MENU)
            {

                camera.x = 0;
                camera.y = 0;

                SDL_Delay(30);

                mainMenu.render();

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




                //update sprites
                hero1.update();

                // render sprites after collision detection
                for (std::vector<Sprite>::size_type i = 0; i < planets.size(); i++)
                {

                }

                hero1.Sprite::render(camera.x, camera.y);
                hero1.Hero::renderBullets(camera.x,camera.y);

            }

            // !! EVERYTHING after this gets executed regardless of game state !!

            // FPS limiter
            // If frame finished early
            ++countedFrames;
            int frameTicks = capTimer.getTicks();
            if( frameTicks < TICKS_PER_FRAME )
            {
                SDL_Delay( TICKS_PER_FRAME - frameTicks );
            }


            // <---- DEBUG HUD
            // takes FPS from capTimer which gets reset each frame, not averaged out

            if(isDebug)
            {
                std::string debug = (std::string)SDL_GetPlatform() + " "
                                    + std::to_string(SDL_GetCPUCount()) + "xCPU "
                                    + std::to_string(SDL_GetSystemRAM()) + "MB RAM";

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
                gTextTexture.loadFromRenderedText( "camera: " + std::to_string(camera.x) + "," + std::to_string(camera.y), gFont12,  red );
                gTextTexture.render( 10, 85 );
            }
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
