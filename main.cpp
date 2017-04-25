
#include "main.h"

Hero hero1;

GameState mainState = MAIN_MENU; // see main.h
short menuSelector = 0;


bool isDebug = true; // debug flag
std::string DMSG; // debug msg

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int LEVEL_WIDTH = 350000;
const int LEVEL_HEIGHT = 350000;

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

const int CAPPED_FPS = 80;
const int TICKS_PER_FRAME = 1000 / CAPPED_FPS;

// pre defined colours
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

        Sprite sol(7000, 7000, yellow, 0, 0, true , 0, "null"); // we all get that its the sun, no label
        sol.setPosition({LEVEL_WIDTH/2 - sol.getWidth().x/2,LEVEL_HEIGHT/2 - sol.getWidth().y/2 });
        planets.push_back(sol);
        sprites.push_back(sol); // add to list of sprites

        Sprite mercury(24, 24, white, 6000, 40 , true , 0 ,"mercury");
        planets.push_back(mercury);
        sprites.push_back(mercury);

        Sprite venus(60, 60, orange, 8500, 62, false,  0,"venus");
        planets.push_back(venus);
        sprites.push_back(venus);

        Sprite terra(63, 63, blue, 11000, 100, true, 0,"terra");
        planets.push_back(terra);
        sprites.push_back(terra);

        Sprite luna(17, 17, brown, 450, 3, true, 3,"luna");
        planets.push_back(luna);
        sprites.push_back(luna);

        Sprite mars(33, 33, red, 14000, 188, true, 0,"mars");
        planets.push_back(mars);
        sprites.push_back(mars);

        Sprite phobos(3, 3, darkorange, 200, 2, true, 5,"phobos");
        planets.push_back(phobos);
        sprites.push_back(phobos);

        Sprite deimos(2, 2, red, 450, 4, true, 5,"deimos");
        planets.push_back(deimos);
        sprites.push_back(deimos);

        Sprite ceres(20, 20, darkorange, 22050, 459, true, 0,"ceres");
        planets.push_back(ceres);
        sprites.push_back(ceres);

        Sprite jupiter(700, 700, brown, 30000, 1200, true, 0,"jupiter");
        planets.push_back(jupiter);
        sprites.push_back(jupiter);

        Sprite ganymede(26, 26, brown, 1300, 20, true, 9,"ganymede");
        planets.push_back(ganymede);
        sprites.push_back(ganymede);

        Sprite europa(15, 15, brown, 1050, 10, true, 9,"europa");
        planets.push_back(europa);
        sprites.push_back(europa);

        Sprite callisto(24, 24, brown, 2000, 40,  true, 9,"callisto");
        planets.push_back(callisto);
        sprites.push_back(callisto);

        Sprite io(18, 18, brown, 800, 3, true, 9,"io");
        planets.push_back(io);
        sprites.push_back(io);

        Sprite saturn(580, 580, red, 55000, 2946, true, 0,"saturn");
        planets.push_back(saturn);
        sprites.push_back(saturn);

        Sprite titan(25, 25, yellow, 1200, 8, true, 14,"titan");
        planets.push_back(titan);
        sprites.push_back(titan);

        Sprite uranus(250, 250, lightblue, 80000, 8400, false, 0,"uranus");
        planets.push_back(uranus);
        sprites.push_back(uranus);

        Sprite neptune(240, 240, blue, 110000, 16480, true, 0,"neptune");
        planets.push_back(neptune);
        sprites.push_back(neptune);

        Sprite triton(13, 13, blue, 500, 67000, true, 17,"triton");
        planets.push_back(triton);
        sprites.push_back(triton);

        Sprite pluto(13, 13, brown, 140000, 24800, true, 0,"pluto");
        planets.push_back(pluto);
        sprites.push_back(pluto);
        // end planet definitions


        std::vector<Sprite> stars1; // not added to master list of sprites
        for(int i = 0; i<5000; i++)
        {
            // TODO: find better divider const than 10
            Sprite newstar;
            newstar.setPosition({rand() % LEVEL_WIDTH/10 , rand() % LEVEL_HEIGHT/10});
            newstar.setWidth({1,1});
            newstar.setColour( {(rand() % 100)+155 , (rand() % 100)+155 , 0 } );
            newstar.setDepth((rand() % 30) + 10 );
            stars1.push_back(newstar);
        }

        //inner belt
        std::vector<Sprite> asteroids1;
        for(int i = 0; i<1000; i++)
        {
            int diam = (rand() % 5) + 5;
            Sprite newast(diam, diam, blue, 22000 + (rand() % 2000), 1000 + rand() % 300 , true, 0, "null");
            newast.setColour( { 0, rand() % 255 , rand() % 255 } );
            asteroids1.push_back(newast);
            sprites.push_back(newast);
        }

        //Kuiper belt
        std::vector<Sprite> asteroids2;
        for(int i = 0; i<2000; i++)
        {
            int diam = (rand() % 5) + 5;
            Sprite newast(diam, diam, green, 120000 + (rand() % 55000), 50000 , true, 0, "null");
            newast.setColour( { 0, rand() % 255 , rand() % 255 } );
            asteroids2.push_back(newast);
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
            camera.x =  hero1.getPosition().x - SCREEN_WIDTH/2;
            camera.y =  hero1.getPosition().y - SCREEN_HEIGHT/2;

            //Keep the camera in bounds
            if( camera.x < 0 ) { camera.x = 0; }
            if( camera.y < 0 ) { camera.y = 0; }
            if( camera.x > LEVEL_WIDTH - camera.w ) { camera.x = LEVEL_WIDTH - camera.w; }
            if( camera.y > LEVEL_HEIGHT - camera.h ) { camera.y = LEVEL_HEIGHT - camera.h; }

            if(mainState==LEVEL1)
            {
                // renders stars and minimap for gameplay
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

                    asteroids1[i].setPosition({newRect.x,newRect.y});
                    asteroids1[i].render(camera.x,camera.y);
            }
            for (std::vector<Sprite>::size_type i = 0; i < asteroids2.size(); i++)
            {
                    asteroids2[i].update();

                    SDL_Rect newRect;
                    newRect = changeAngle(planets[asteroids2[i].getRotating()],asteroids2[i], 10.f/ asteroids2[i].getPeriod());

                    asteroids2[i].setPosition({newRect.x,newRect.y});
                    asteroids2[i].render(camera.x,camera.y);
            }

            for (std::vector<Sprite>::size_type i = 0; i < planets.size(); i++)
            {
                planets[i].update();

                SDL_Rect newRect;
                if(i!=0)
                {
                    newRect = changeAngle(planets[planets[i].getRotating()],planets[i], 10.f/ planets[i].getPeriod()) ;

                    planets[i].setPosition({newRect.x,newRect.y});

                }

                planets[i].render(camera.x,camera.y);

                newRect = planets[i].getRect();
                if (hero1.checkCollision(&newRect))
                {
                    hero1.collisionResponse(newRect);

                    circleColor(gRenderer, hero1.getCentre().x - camera.x, hero1.getCentre().y - camera.y , 13, 0xFF0000FF);
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

                hero1.Sprite::render(camera.x, camera.y);
                hero1.Hero::renderBullets(camera.x,camera.y);

            }

            // !! EVERYTHING after this gets executed regardless of game state !!
            // FPS limiter - If frame finished early, delay
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

                gTextTexture.loadFromRenderedText( std::to_string( (int) (1000.f / capTimer.getTicks()) ) + " fps" , gFont16,  red );
                gTextTexture.render( 10, 25 );

                double theta = getTheta(hero1,planets[0]) * 180.0/3.141593;;
                if (theta<0) theta+=360; // weird degree conversion, cant explain

                gTextTexture.loadFromRenderedText( std::to_string(theta), gFont12,  red );
                gTextTexture.render( 10, 55 );
                gTextTexture.loadFromRenderedText( std::to_string(hero1.getPosition().x) + ", "
                                                + std::to_string(hero1.getVelocity().x) + " / "
                                                + std::to_string(hero1.getPosition().y) + ", "
                                                + std::to_string(hero1.getVelocity().y)
                                                , gFont12,  red );
                gTextTexture.render( 10, 70 );
                gTextTexture.loadFromRenderedText( "camera: " + std::to_string(camera.x) + "," + std::to_string(camera.y), gFont12,  red );
                gTextTexture.render( 10, 85 );
            }
            // END DEBUG HUD section --->

                gTextTexture.loadFromRenderedText("RED - ", gFont24, red );
                gTextTexture.render( 35,SCREEN_HEIGHT-110);
                gTextTexture.loadFromRenderedText("GREEN - ", gFont24, green );
                gTextTexture.render( 35,SCREEN_HEIGHT-80);
                gTextTexture.loadFromRenderedText("BLUE - ", gFont24, blue );
                gTextTexture.render( 35,SCREEN_HEIGHT-50);

                gTextTexture.loadFromRenderedText("HEALTH - " + std::to_string( (int) hero1.getHealth()) + "%", gFont24, orange );
                gTextTexture.render( SCREEN_WIDTH-250,SCREEN_HEIGHT-50);

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
