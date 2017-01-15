#ifndef MENU_H
#define MENU_H

#include "main.h"

class Menu
{
	protected:

        std::string titles[8];

        int menuTimer;



    public:

        Menu();

        void render();


};

#endif
