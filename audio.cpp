#include "main.h"
#include "audio.h"

//The music that will be played
extern Mix_Music *bgMusic;

extern Mix_Chunk *sfx1;

void audioToggleBG()
{

    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( bgMusic, -1 );
    }
    //If music is being played
    else
    {
        //If the music is paused
        if( Mix_PausedMusic() == 1 )
        {
            //Resume the music
            Mix_ResumeMusic();
        }
        //If the music is playing
        else
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }
}

void audioStop()
{
    Mix_HaltMusic();

}

// call before closing application
void audioCleanup()
{
     //Free the music
    Mix_FreeMusic( bgMusic );
    bgMusic = NULL;

    Mix_FreeChunk( sfx1 );
    sfx1 = NULL;

    Mix_Quit();

}
