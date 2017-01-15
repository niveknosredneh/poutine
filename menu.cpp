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

            gTextTexture.render( SCREEN_WIDTH/3, SCREEN_HEIGHT/3 + i*30);
        }


    }

    if (!(menuTimer % 5))
    {
        gTextTexture.loadFromRenderedText( "P" , gFont24,  red );
        gTextTexture.render( SCREEN_WIDTH/3 + 5, SCREEN_HEIGHT/5);
    }
    if (!(menuTimer % 6))
    {
        gTextTexture.loadFromRenderedText( "I" , gFont24,  blue);
        gTextTexture.render( SCREEN_WIDTH/3 + 30, SCREEN_HEIGHT/5);
    }
    if (!(menuTimer % 7))
    {
        gTextTexture.loadFromRenderedText( "K" , gFont24,  green);
        gTextTexture.render( SCREEN_WIDTH/3 + 50, SCREEN_HEIGHT/5);
    }
    if (!(menuTimer % 8))
    {
        gTextTexture.loadFromRenderedText( "S" , gFont24,  yellow);
        gTextTexture.render( SCREEN_WIDTH/3 + 80, SCREEN_HEIGHT/5);
    }
    if (!(menuTimer % 9))
    {
        gTextTexture.loadFromRenderedText( "U" , gFont24,  cyan);
        gTextTexture.render( SCREEN_WIDTH/3 + 107, SCREEN_HEIGHT/5);
    }
    if (!(menuTimer % 10))
    {
        gTextTexture.loadFromRenderedText( "L" , gFont24,  magenta);
        gTextTexture.render( SCREEN_WIDTH/3 + 140, SCREEN_HEIGHT/5);
    }


    menuTimer++;
}


