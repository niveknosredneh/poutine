#include "main.h"
#include "menu.h"

extern SDL_Color darkgray, white, red, blue, green, yellow, cyan, magenta;


extern TTF_Font *gFont24, *gFont40;
extern int menuTimer;


Menu::Menu(std::vector<std::string> titleList)
{
    titles = titleList;

    menuSelector = 0;
    menuTimer = 0;

}

void Menu::render()
{
    if(menuSelector<0) menuSelector=0;
    if(menuSelector>titles.size()-1) menuSelector=titles.size()-1;



    for (int i = 0; i < titles.size() ; i++)
    {
        if( titles[i] != "")
        {
            if(menuSelector==i) gTextTexture.loadFromRenderedText( titles[i] , gFont24,  white);
            else                gTextTexture.loadFromRenderedText( titles[i] , gFont24,  darkgray);

            gTextTexture.render( SCREEN_WIDTH/3, SCREEN_HEIGHT/2.3 + i*30);
        }
    }

    gTextTexture.loadFromRenderedText( "O R B I T A L" , gFont40, white);
    gTextTexture.render( SCREEN_WIDTH/2.3 , SCREEN_HEIGHT/4);

    gTextTexture.loadFromRenderedText( "O F F E N S E" , gFont40, white);
    gTextTexture.render( SCREEN_WIDTH/2.3 , SCREEN_HEIGHT/4 + 38);

    menuTimer++;
}

short Menu::getMenuSelector() { return menuSelector; }

void Menu::setMenuSelector(short newshort)
{
    menuSelector = newshort;
}


