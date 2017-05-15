#include "main.h"


bool eventHandler()
{
	extern Hero hero1;
	extern SDL_Rect camera;
	extern std::vector<Sprite>::size_type cameraTarget;
	extern Menu mainMenu, optionsMenu, quitMenu;

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	int x, y;
	Uint32 currentMouseState = SDL_GetMouseState(&x, &y);

	// draws crosshair
	double theta = getTheta({x,y},hero1.getPosition());
	SDL_SetRenderDrawColor( gRenderer, 0x40, 0x40, 0x40, 0xFF );
	SDL_RenderDrawLine(gRenderer,x-20*cos(theta),y+20*sin(theta),x+20*cos(theta),y-20*sin(theta));
	SDL_RenderDrawLine(gRenderer,x-20*sin(theta),y-20*cos(theta),x+20*sin(theta),y+20*cos(theta));



	//If mouse event happened
	if( currentMouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        hero1.shoot(x+camera.x,y+camera.y);
    }
    //If mouse event happened
	if( currentMouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {

    }




    // ESCAPE
    if( currentKeyStates[ SDL_SCANCODE_ESCAPE ] )
	{
        SDL_Delay(50);
        if(mainState == MAIN_MENU) mainState = QUIT;
		else if(mainState==QUIT) ; // do nothing
		else mainState = MAIN_MENU;

	}



	if( currentKeyStates[ SDL_SCANCODE_LCTRL ] )
	{
		hero1.chargeShield();
	}
	if( currentKeyStates[ SDL_SCANCODE_LALT ] )
	{

	}
    if( currentKeyStates[ SDL_SCANCODE_TAB ] )
	{
        if(cameraTarget==planets.size()-1)
        {
            cameraTarget=-1;
        }
        else cameraTarget++;
	}



    // UP DOWN LEFT RIGHT
	if( currentKeyStates[ SDL_SCANCODE_UP ] )
	{

	}
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
	{

	}
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{

	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{

	}




    if( currentKeyStates[ SDL_SCANCODE_SPACE ] )
	{


	}
    if( currentKeyStates[ SDL_SCANCODE_RETURN ] )
	{
        if(mainState==QUIT)
		{
            if(quitMenu.getMenuSelector()==0) mainState = MAIN_MENU;
            else if(quitMenu.getMenuSelector()==1) close();
        }
        if(mainState==MAIN_MENU)
		{
            if(mainMenu.getMenuSelector()==0) mainState = LEVEL1;
            else if(mainMenu.getMenuSelector()==1) mainState = MULTIPLAYER;
            else if(mainMenu.getMenuSelector()==2) mainState = OPTIONS;
            else if(mainMenu.getMenuSelector()==3) mainState = QUIT;
        }
		if(mainState==DEATH) mainState = MAIN_MENU;

        if(mainState==OPTIONS)
		{
            //if(optionsMenu.getMenuSelector()==0) mainState = LEVEL1;
            //else if(mainMenu.getMenuSelector()==1) mainState = MULTIPLAYER;
            //else if(mainMenu.getMenuSelector()==2) mainState = OPTIONS;
            if(optionsMenu.getMenuSelector()==3) mainState = MAIN_MENU;
        }


	}


    if( currentKeyStates[ SDL_SCANCODE_W ] )
	{
	    if(mainState==MAIN_MENU) mainMenu.setMenuSelector(mainMenu.getMenuSelector()-1);
        else if(mainState==OPTIONS) optionsMenu.setMenuSelector(optionsMenu.getMenuSelector()-1);
        else if(mainState==QUIT) quitMenu.setMenuSelector(mainMenu.getMenuSelector()-1);
		else hero1.moveUp();
	}
    if( currentKeyStates[ SDL_SCANCODE_A ] )
	{
		hero1.moveLeft();
	}
    if( currentKeyStates[ SDL_SCANCODE_S ] )
	{
        if(mainState==MAIN_MENU) mainMenu.setMenuSelector(mainMenu.getMenuSelector()+1);
        else if(mainState==OPTIONS) optionsMenu.setMenuSelector(optionsMenu.getMenuSelector()+1);
        else if(mainState==QUIT) quitMenu.setMenuSelector(mainMenu.getMenuSelector()+1);
		else hero1.moveDown();
	}
    if( currentKeyStates[ SDL_SCANCODE_D ] )
	{
		hero1.moveRight();
	}


    if( currentKeyStates[ SDL_SCANCODE_M ] )
	{
        hero1.setPosition({planets[3].getPosition().x-100,planets[3].getPosition().y-100});
	}
    if( currentKeyStates[ SDL_SCANCODE_EQUALS ] )
	{

	}

	// Function keys
    if( currentKeyStates[ SDL_SCANCODE_F10 ] )
	{
        audioToggleBG();
	}
    if( currentKeyStates[ SDL_SCANCODE_F9 ] )
	{
        isDebug = !isDebug;
	}
	return true;

}
