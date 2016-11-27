#ifndef MENU_H
#define MENU_H

#include "main.h"

class Menu
{
	protected:

        std::vector<std::string> titlesVec;

        SDL_Color colour1;
        SDL_Color colour2;



    public:

        Menu(std::vector<std::string>,SDL_Color,SDL_Color);

        void mainMenu();
        void render();


};

#endif
