#include "main.h"
#include "menu.h"

extern SDL_Color darkgray, white, red, blue, green, yellow, cyan, magenta;


extern TTF_Font *gFont24;
extern int menuTimer;


Menu::Menu()
{
    titles[0] = "solo play";
    titles[1] = "multi play";
    titles[2] = "options";
    titles[3] = "exit";


    menuTimer = 0;

}

void Menu::render()
{

    for (int i = 0; i < 4 ; i++)
    {
        if( titles[i] != "")
        {
            if(menuSelector==i) gTextTexture.loadFromRenderedText( titles[i] , gFont24,  white);
            else                gTextTexture.loadFromRenderedText( titles[i] , gFont24,  darkgray);

            gTextTexture.render( SCREEN_WIDTH/3, SCREEN_HEIGHT/2.3 + i*30);
        }


    }


    gTextTexture.loadFromRenderedText( "O R B I T A L" , gFont24, darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 , SCREEN_HEIGHT/3);

    gTextTexture.loadFromRenderedText( "O F F E N S E" , gFont24, darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 , SCREEN_HEIGHT/3 + 35);




    menuTimer++;
}


