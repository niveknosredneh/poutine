#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_net.h>

#include <stdio.h>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <thread> // implement threads
#include <semaphore.h> // implement semaphores

#include "main.h"

#include "timer.h"
#include "init.h"
#include "eventHandler.h"
#include "audio.h"
#include "texture.h"
#include "sprite.h"
#include "hero.h"
#include "bullet.h"
#include "io.h"
#include "network.h"
#include "menu.h"
#include "mymath.h"

extern std::string DMSG;

enum GameState { INTRO, MAIN_MENU, LEVEL1, DEATH, MULTIPLAYER, OPTIONS, QUIT };

void menuSelect(int);

void focusCamera(int target);

//The window we'll be rendering to
extern SDL_Window* gWindow;

extern Hero hero1;

extern std::vector<Sprite> planets;

extern GameState mainState;

extern Texture gTextTexture;

//The window renderer
extern SDL_Renderer* gRenderer;

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;

int main( int argc, char* args[] );


#endif
