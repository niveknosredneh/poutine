
#include "main.h"

Hero hero1;

std::vector<Sprite> planets;

GameState mainState = INTRO; // see main.h

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

double ZOOMx = 2;

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
std::vector<Sprite>::size_type cameraTarget = -1;

// timer init
Timer fpsTimer, capTimer; // Timer object

const int CAPPED_FPS = 30;
const int TICKS_PER_FRAME = 1000 / CAPPED_FPS;

// pre defined colours
SDL_Color red   = {255, 64, 64};
SDL_Color green = {64,255,64};
SDL_Color blue  = {64, 64, 255};
SDL_Color lightblue  = {113, 187, 249};
SDL_Color white = {255,255,255};
SDL_Color darkgray = {69,69,69};
SDL_Color orange = {221, 131, 16};
SDL_Color darkorange = {166, 115, 4};
SDL_Color yellow   = {255,255,0};
SDL_Color cyan   = {0,255,255};
SDL_Color magenta   = {255,0,255};
SDL_Color brown   = {109, 54, 43};
SDL_Color black = {0,0,0};

std::vector<std::string> menuVector = { "solo play" ,  "multi play", "options",  "exit" };
Menu mainMenu(menuVector);
std::vector<std::string> optionsVector = { "team" ,  "other placeholder", "stuff", "exit" };
Menu optionsMenu(optionsVector);
std::vector<std::string> quitVector = { "no", "yes" };
Menu quitMenu(quitVector);

//Globally used font
TTF_Font *gFont40 = NULL;
TTF_Font *gFont24 = NULL;
TTF_Font *gFont16 = NULL;
TTF_Font *gFont12 = NULL;
TTF_Font *tFont40 = NULL;

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
		focusCamera(-1); // focuses on hero

        // begin Planet definitions
        Sprite sol(7000, 100, yellow, 0, 0, true , 0, "sun");
        sol.setPosition({LEVEL_WIDTH/2 - sol.getWidth().x/2,LEVEL_HEIGHT/2 - sol.getWidth().y/2 });
        planets.push_back(sol);
        sprites.push_back(sol); // add to list of sprites

        Sprite mercury(24, 1,white, 6000, 40 , true , 0 ,"mercury");
        planets.push_back(mercury);
        sprites.push_back(mercury);

        Sprite venus(60, 1,orange, 8500, 62, false,  0,"venus");
        planets.push_back(venus);
        sprites.push_back(venus);

        Sprite terra(63, 6,blue, 11000, 100, true, 0,"earth");
        planets.push_back(terra);
        sprites.push_back(terra);

        Sprite luna(17, 1,brown, 450, 5, true, 3,"luna");
        planets.push_back(luna);
        sprites.push_back(luna);

        Sprite mars(33, 1,red, 14000, 188, true, 0,"mars");
        planets.push_back(mars);
        sprites.push_back(mars);

        Sprite phobos(3, 1,darkorange, 200, 2, true, 5,"phobos");
        planets.push_back(phobos);
        sprites.push_back(phobos);

        Sprite deimos(2, 1,red, 450, 4, true, 5,"deimos");
        planets.push_back(deimos);
        sprites.push_back(deimos);

        Sprite ceres(20, 1,darkorange, 22050, 459, true, 0,"ceres");
        planets.push_back(ceres);
        sprites.push_back(ceres);

        Sprite jupiter(700, 100, brown, 33000, 1200, true, 0,"jupiter");
        planets.push_back(jupiter);
        sprites.push_back(jupiter);

        Sprite ganymede(26, 1,brown, 1300, 20, true, 9,"ganymede");
        planets.push_back(ganymede);
        sprites.push_back(ganymede);

        Sprite europa(15, 1,brown, 1050, 10, true, 9,"europa");
        planets.push_back(europa);
        sprites.push_back(europa);

        Sprite callisto(24, 1,brown, 2000, 40,  true, 9,"callisto");
        planets.push_back(callisto);
        sprites.push_back(callisto);

        Sprite io(18, 1,brown, 800, 3, true, 9,"io");
        planets.push_back(io);
        sprites.push_back(io);

        Sprite saturn(580, 57, red, 55000, 2946, true, 0,"saturn");
        planets.push_back(saturn);
        sprites.push_back(saturn);

        Sprite titan(25, 1,yellow, 1200, 8, true, 14,"titan");
        planets.push_back(titan);
        sprites.push_back(titan);

        Sprite uranus(250, 1,lightblue, 80000, 8400, false, 0,"uranus");
        planets.push_back(uranus);
        sprites.push_back(uranus);

        Sprite neptune(240, 10,blue, 110000, 16480, true, 0,"neptune");
        planets.push_back(neptune);
        sprites.push_back(neptune);

        Sprite triton(13, 1,blue, 500, 67000, true, 17,"triton");
        planets.push_back(triton);
        sprites.push_back(triton);

        Sprite pluto(13, 1,brown, 140000, 24800, true, 0,"pluto");
        planets.push_back(pluto);
        sprites.push_back(pluto);
        // end planet definitions


        std::vector<Sprite> stars1; // not added to master list of sprites
        for(int i = 0; i<6000; i++)
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
        for(int i = 0; i<300; i++)
        {
            int diam = (rand() % 5) + 5;
            Sprite newast(diam, 1,blue, 18000 + (rand() % 10000), 100 + rand() % 300 , true, 0, "null");
            newast.setColour( blue );
            asteroids1.push_back(newast);
            sprites.push_back(newast);
        }

        //Kuiper belt
        std::vector<Sprite> asteroids2;
        for(int i = 0; i<400; i++)
        {
            int diam = (rand() % 5) + 5;
            Sprite newast(diam, 1,green, 110000 + (rand() % 65000), 1000 + rand() % 2000 , true, 0, "null");
            newast.setColour( blue );
            asteroids2.push_back(newast);
            sprites.push_back(newast);
        }


		fpsTimer.start(); //Start counting frames per second
		int countedFrames = 0;
		// end timer init

        // disabled networking
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

            focusCamera(cameraTarget);

            //Keep the camera in bounds
            if( camera.x < 0 ) { camera.x = 0; }
            if( camera.y < 0 ) { camera.y = 0; }
            if( camera.x > LEVEL_WIDTH - camera.w ) { camera.x = LEVEL_WIDTH - camera.w; }
            if( camera.y > LEVEL_HEIGHT - camera.h ) { camera.y = LEVEL_HEIGHT - camera.h; }

            if(mainState==INTRO)
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
                if(fpsTimer.getTicks()/100 > 1)
                {
                    SDL_RenderDrawLine(gRenderer,580,0,580,660 );
                }

                if(fpsTimer.getTicks()/100 > 4)
                {
                    gTextTexture.loadFromRenderedText( "Pixel Plumber Studios", tFont40,  {white.r,white.g,white.b+fpsTimer.getTicks()/40} );
                    gTextTexture.render( 600, 600 );
                    SDL_RenderDrawLine(gRenderer,580,660,1500,660);
                }

                if(fpsTimer.getTicks()/100 > 9)
                {
                    gTextTexture.loadFromRenderedText( "Presents ...", tFont40,  white );
                    gTextTexture.render( 1200, 680 );
                    SDL_RenderDrawLine(gRenderer,1500,660,1500,SCREEN_HEIGHT);
                }

                if(fpsTimer.getTicks()/100 > 15)
                {
                    //clear the screen
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                    SDL_RenderClear( gRenderer );
                    mainState = MAIN_MENU;
                }
            }

            if(mainState==LEVEL1)
            {

                // renders stars and minimap for gameplay
                // renders all stars
                for (std::vector<Sprite>::size_type i = 0; i < stars1.size(); i++) stars1[i].render(camera.x,camera.y);

                // creates mini map boundary
                SDL_SetRenderDrawColor( gRenderer, 0XFF, 0XFF, 0XFF, 0xFF );
                SDL_Rect newRect = {5*SCREEN_WIDTH/6 - 2, 0 , SCREEN_WIDTH/6 + 4, SCREEN_HEIGHT/3 + 6};
                SDL_RenderFillRect( gRenderer, &newRect );
                SDL_SetRenderDrawColor( gRenderer, 0X00, 0X00, 0X00, 0xFF );
                newRect = {5*SCREEN_WIDTH/6, 2 , SCREEN_WIDTH/6 - 2, SCREEN_HEIGHT/6};
                SDL_RenderFillRect( gRenderer, &newRect ); // map1
                newRect = {5*SCREEN_WIDTH/6, SCREEN_HEIGHT/6 + 4 , SCREEN_WIDTH/6 - 2, SCREEN_HEIGHT/6};
                SDL_RenderFillRect( gRenderer, &newRect ); // map2
                // end mini map boundary

                // update sprites
                hero1.update();

                for(int i=0;i<15;i++) // exhaust
                {
                    int rIntX = rand() % hero1.getWidth().x;
                    int rIntY = rand() % hero1.getWidth().y;
                    SDL_SetRenderDrawColor( gRenderer, 0, 0x00, rand() % 255, 0xFF );
                    SDL_RenderDrawLine(gRenderer, hero1.getPosition().x + hero1.getWidth().x/2- rIntX -camera.x, hero1.getPosition().y + hero1.getWidth().y/2 - rIntY-camera.y, hero1.getPosition().x + hero1.getWidth().x/2 - rIntX - (hero1.getVelocity().x) - camera.x , hero1.getPosition().y + hero1.getWidth().y/2 - rIntY - (hero1.getVelocity().y) - camera.y);

                }

                hero1.Sprite::render(camera.x, camera.y);
                hero1.renderBullets(camera.x,camera.y);

                // START HUD
                SDL_Rect redBar = {20, SCREEN_HEIGHT-120 , 255, 20};
                SDL_Rect redBar2 = {20, SCREEN_HEIGHT-120 , hero1.getR(), 20};
                SDL_SetRenderDrawColor( gRenderer, 100, 0x00, 0x00, 0xFF );
                SDL_RenderFillRect(gRenderer, &redBar);
                SDL_SetRenderDrawColor( gRenderer, 200, 0x00, 0x00, 0xFF );
                SDL_RenderDrawRect(gRenderer, &redBar);
                SDL_RenderFillRect(gRenderer, &redBar2);
                gTextTexture.loadFromRenderedText(intToHexString(hero1.getR()), gFont24, black );
                gTextTexture.render( 135,SCREEN_HEIGHT-125);

                SDL_Rect greenBar = {20, SCREEN_HEIGHT-80 , 255, 20};
                SDL_Rect greenBar2 = {20, SCREEN_HEIGHT-80 , hero1.getG(), 20};
                SDL_SetRenderDrawColor( gRenderer, 0, 100, 0x00, 0xFF );
                SDL_RenderFillRect(gRenderer, &greenBar);
                SDL_SetRenderDrawColor( gRenderer, 0, 200, 0x00, 0xFF );
                SDL_RenderDrawRect(gRenderer, &greenBar);
                SDL_RenderFillRect(gRenderer, &greenBar2);
                gTextTexture.loadFromRenderedText(intToHexString(hero1.getG()), gFont24, black );
                gTextTexture.render( 135,SCREEN_HEIGHT-85);

                SDL_Rect blueBar = {20, SCREEN_HEIGHT-40 , 255, 20};
                SDL_Rect blueBar2 = {20, SCREEN_HEIGHT-40 , hero1.getB(), 20};
                SDL_SetRenderDrawColor( gRenderer, 0, 0x00, 100, 0xFF );
                SDL_RenderFillRect(gRenderer, &blueBar);
                SDL_SetRenderDrawColor( gRenderer, 0, 0x00, 200, 0xFF );
                SDL_RenderDrawRect(gRenderer, &blueBar);
                SDL_RenderFillRect(gRenderer, &blueBar2);
                gTextTexture.loadFromRenderedText(intToHexString(hero1.getB()) , gFont24, black );
                gTextTexture.render( 135,SCREEN_HEIGHT-45);

                SDL_Rect healthBar = {SCREEN_WIDTH - 20 - 255, SCREEN_HEIGHT-60 , 255, 30};
                SDL_Rect healthBar2 = {SCREEN_WIDTH - 20 - 255, SCREEN_HEIGHT-60 , hero1.getHealth(), 30};
                SDL_SetRenderDrawColor( gRenderer, 100, 100, 100, 0xFF );
                SDL_RenderFillRect(gRenderer, &healthBar);
                SDL_SetRenderDrawColor( gRenderer, 200, 200, 200, 0xFF );
                SDL_RenderDrawRect(gRenderer, &healthBar);
                SDL_RenderFillRect(gRenderer, &healthBar2);
                gTextTexture.loadFromRenderedText(intToHexString(hero1.getHealth()) , gFont24, black );
                gTextTexture.render( SCREEN_WIDTH - 150 , SCREEN_HEIGHT-55);

                SDL_Rect shieldBar = {SCREEN_WIDTH - 20 - 255, SCREEN_HEIGHT-120 , 255, 30};
                SDL_Rect shieldBar2 = {SCREEN_WIDTH - 20 - 255, SCREEN_HEIGHT-120 , hero1.getShieldCharge(), 30};
                SDL_SetRenderDrawColor( gRenderer, 0, 100, 0, 0xFF );
                SDL_RenderFillRect(gRenderer, &shieldBar);
                SDL_SetRenderDrawColor( gRenderer, 0, 200, 0, 0xFF );
                SDL_RenderDrawRect(gRenderer, &shieldBar);
                SDL_RenderFillRect(gRenderer, &shieldBar2);
                gTextTexture.loadFromRenderedText(intToHexString(hero1.getShieldCharge()) , gFont24, black );
                gTextTexture.render( SCREEN_WIDTH - 150 , SCREEN_HEIGHT-115);
                // END HUD

            }

            // renders all asteroids
            for (std::vector<Sprite>::size_type i = 0; i < asteroids1.size(); i++)
            {
                asteroids1[i].update();
                if(checkCollision(hero1,asteroids2[i])==true)
                    hero1.damage(15);

                asteroids1[i].render(camera.x,camera.y);
            }
            for (std::vector<Sprite>::size_type i = 0; i < asteroids2.size(); i++)
            {
                asteroids2[i].update();
                if(checkCollision(hero1,asteroids2[i])==true)
                    hero1.damage(15);

                asteroids2[i].render(camera.x,camera.y);
            }

            // planets
            for (std::vector<Sprite>::size_type i = 0; i < planets.size(); i++)
            {

                if(i>0) planets[i].update(); // dont update the sun, it shouldnt move

                // pull hero towards planet
                double Radius = getRadius(hero1.getPosition(),planets[i].getPosition());
                hero1.bePulled(planets[i], hero1.getMass()*planets[i].getMass()/ Radius);
                // end pull

                if(checkCollision(hero1,planets[i])==true)
                {
                    hero1.setPosition({hero1.getPosition().x-hero1.getVelocity().x,hero1.getPosition().y-hero1.getVelocity().y});
                    hero1.setVelocity({0,0});
                    hero1.damage(50);
                }
                planets[i].render(camera.x,camera.y);
            }


            // !! everything before this point inside the main loop gets executed regardless of game state !!
            if(mainState==QUIT)
            {
                SDL_Delay(100);
                //gTextTexture.loadFromRenderedText("are you sure you want to leave?", gFont24, white );
                //gTextTexture.render( SCREEN_WIDTH/2.3, SCREEN_HEIGHT/2.1);
                quitMenu.render();
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
                SDL_Delay(100);
                optionsMenu.render();
            }

            if(mainState == MULTIPLAYER)
            {
                //havent gotten this far
                mainState = MAIN_MENU;
            }

            if(mainState == LEVEL1)
            {



            }

            if(mainState == DEATH) // player has died, can no longer control like in gamestate LEVEL1
            {


                //clear the screen
                SDL_SetRenderDrawColor( gRenderer, 0x22, 0x00, 0x00, 0xFF );
                SDL_RenderClear( gRenderer );

                gTextTexture.loadFromRenderedText( "Time is infinite, you are not", gFont24,  red );
                gTextTexture.render( SCREEN_HEIGHT-300, SCREEN_WIDTH/2 - 50 );

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

                gTextTexture.loadFromRenderedText( debug, gFont12,  blue );
                gTextTexture.render( 10, 10 );

                gTextTexture.loadFromRenderedText( std::to_string( (int) (1000.f / capTimer.getTicks()) ) + " fps" , gFont16,  blue );
                gTextTexture.render( 10, 25 );

                gTextTexture.loadFromRenderedText( std::to_string(fpsTimer.getTicks()), gFont12,  blue );
                gTextTexture.render( 10, 55 );
                gTextTexture.loadFromRenderedText( std::to_string(hero1.getPosition().x) + ", "
                                                + std::to_string(hero1.getVelocity().x) + " / "
                                                + std::to_string(hero1.getPosition().y) + ", "
                                                + std::to_string(hero1.getVelocity().y)
                                                , gFont12,  blue );
                gTextTexture.render( 10, 70 );
                gTextTexture.loadFromRenderedText( "camera: " + std::to_string(camera.x) + "," + std::to_string(camera.y), gFont12,  blue );
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

void focusCamera(int target)
{
        if(target==-1)
        {// where to place vision
            camera.x =  hero1.getPosition().x - SCREEN_WIDTH/2;
            camera.y =  hero1.getPosition().y - SCREEN_HEIGHT/2;
        }
        else
        {// where to place vision
            camera.x =  planets[target].getPosition().x - SCREEN_WIDTH/2;
            camera.y =  planets[target].getPosition().y - SCREEN_HEIGHT/2;
        }
}

std::string intToHexString(int intVal)
{
    std::stringstream ss;
    ss << std::hex << intVal; // int decimal_value
    std::string hexS ( ss.str() );

    for(int i = 0; i < hexS.size(); i++)
    {
        hexS.at(i) = toupper(hexS.at(i));
    }

    return hexS;
}



