#include "main.h"
#include "menu.h"


Menu::Menu(std::vector<std::string> titles, SDL_Color c1, SDL_Color c2)
{

    std::vector<std::string> titlesVec = titles;

    SDL_Color colour1 = c1;
    SDL_Color colour2 = c2;

}

void Menu::render()
{

    for (std::vector<std::string>::size_type i = 0; i < titlesVec.size(); i++)
    {

        if(menuSelector==(int)i) gTextTexture.loadFromRenderedText( titlesVec[i] ,  colour1);
        else                gTextTexture.loadFromRenderedText( titlesVec[i] ,  {150,150,150});
        gTextTexture.render( SCREEN_WIDTH/4, SCREEN_HEIGHT/4 );

        std::cout << titlesVec[i];
    }

}


