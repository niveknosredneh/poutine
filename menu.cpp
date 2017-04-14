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


    gTextTexture.loadFromRenderedText( "O" , gFont24, darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 , SCREEN_HEIGHT/5);

    gTextTexture.loadFromRenderedText( "R" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 20, SCREEN_HEIGHT/5);

    gTextTexture.loadFromRenderedText( "B" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 40, SCREEN_HEIGHT/5);

    gTextTexture.loadFromRenderedText( "I" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 60, SCREEN_HEIGHT/5);

    gTextTexture.loadFromRenderedText( "T" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 80, SCREEN_HEIGHT/5);

    gTextTexture.loadFromRenderedText( "A" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/5);

    gTextTexture.loadFromRenderedText( "L" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 120, SCREEN_HEIGHT/5);

    gTextTexture.loadFromRenderedText( "O" , gFont24, darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 , SCREEN_HEIGHT/5 + 35);

    gTextTexture.loadFromRenderedText( "F" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 20, SCREEN_HEIGHT/5 + 35);

    gTextTexture.loadFromRenderedText( "F" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 40, SCREEN_HEIGHT/5 + 35);

    gTextTexture.loadFromRenderedText( "E" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 60, SCREEN_HEIGHT/5 + 35);

    gTextTexture.loadFromRenderedText( "N" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 80, SCREEN_HEIGHT/5 + 35);

    gTextTexture.loadFromRenderedText( "S" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/5 + 35);

    gTextTexture.loadFromRenderedText( "E" , gFont24,  darkgray);
    gTextTexture.render( SCREEN_WIDTH/3 + 120, SCREEN_HEIGHT/5 + 35);


    menuTimer++;
}


