#include "main.h"
#include "init.h"

extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow;

//The music that will be played
Mix_Music *bgMusic = NULL;

Mix_Chunk *sfx1 = NULL;

extern TTF_Font *gFont24, *gFont16, *gFont12;

bool init()
{

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( " ~ PIKSUL ~ ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                //Initialize SDL_mixer
				if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				// init network
                if(SDLNet_Init()==-1)
                {
                    printf("SDL_net could not initialize! SDL_ttf Error: %s\n", SDLNet_GetError());
                    exit(2);
                }
			}
		}
	}

	return success;
}

bool loadMedia()
{

	//Loading success flag
	bool success = true;

	//Load music
	bgMusic = Mix_LoadMUS( "03 Bonobo - Cirrus.mp3" );
	if( bgMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    sfx1 = Mix_LoadWAV( "medium.wav" );
	if( sfx1 == NULL )
	{
		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    //Open the font
	gFont24 = TTF_OpenFont( "verdana.ttf", 24 );
	if( gFont24 == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	gFont16 = TTF_OpenFont( "verdana.ttf", 16 );
	gFont12 = TTF_OpenFont( "verdana.ttf", 12 );

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	audioCleanup();

	//Quit SDL subsystems
	SDLNet_Quit();
	IMG_Quit();
	SDL_Quit();
}

