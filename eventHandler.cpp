#include "main.h"

bool eventHandler()
{
	extern Hero hero1;

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    if( currentKeyStates[ SDL_SCANCODE_ESCAPE ] )
	{
		mainState = MAIN_MENU;
	}
	if( currentKeyStates[ SDL_SCANCODE_LCTRL ] )
	{
		hero1.jump();
	}
	if( currentKeyStates[ SDL_SCANCODE_LALT ] )
	{
		hero1.setYvelocity(0);
	}
	if( currentKeyStates[ SDL_SCANCODE_UP ] )
	{
	    if(mainState==MAIN_MENU)
        {
            menuSelect(-1);
        }
		else
            hero1.moveUp();
	}
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
	{
        if(mainState==MAIN_MENU)
        {
            menuSelect(1);
        }
		else
            hero1.moveDown();
	}
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{
		hero1.moveLeft();
	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		hero1.moveRight();
	}
    if( currentKeyStates[ SDL_SCANCODE_SPACE ] )
	{
		hero1.shoot();

	}
    if( currentKeyStates[ SDL_SCANCODE_RETURN ] )
	{
		if(menuSelector==0) mainState = LEVEL1;
		else if(menuSelector==1) mainState = MULTIPLAYER;
		else if(menuSelector==2) mainState = OPTIONS;
		else if(menuSelector==3) mainState = QUIT;

	}
    if( currentKeyStates[ SDL_SCANCODE_R ] )
	{
		hero1.spawn(500,500);
	}
    if( currentKeyStates[ SDL_SCANCODE_P ] )
	{
        audioToggleBG();
	}
	return true;

}
