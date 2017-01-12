#include "main.h"
#include "menu.h"

extern SDL_Color darkgray;
extern SDL_Color white;

extern TTF_Font *gFont24;


Menu::Menu()
{
    titles[0] = "solo play";
    titles[1] = "multi play";
    titles[2] = "options";
    titles[3] = "exit";


    colour1 = darkgray;
    colour2 = white;

}

void Menu::render()
{

    for (int i = 0; i < 4 ; i++)
    {

        if(menuSelector==i) gTextTexture.loadFromRenderedText( titles[i] , gFont24,  colour2);
        else                gTextTexture.loadFromRenderedText( titles[i] , gFont24,  colour1);

        gTextTexture.render( SCREEN_WIDTH/3, SCREEN_HEIGHT/3 + i*30);

    }

}


