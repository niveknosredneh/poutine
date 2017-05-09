#ifndef MENU_H
#define MENU_H

#include "main.h"

class Menu
{
	protected:

        std::vector<std::string> titles;

        int menuTimer;
        short menuSelector;



    public:

        Menu(std::vector<std::string>);

        void render();

        void setMenuSelector(short);
        short getMenuSelector();



};

#endif
