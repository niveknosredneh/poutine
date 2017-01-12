#ifndef MENU_H
#define MENU_H

#include "main.h"

class Menu
{
	protected:

        std::string titles[4];

        SDL_Color colour1;
        SDL_Color colour2;



    public:

        Menu();

        void render();


};

#endif
