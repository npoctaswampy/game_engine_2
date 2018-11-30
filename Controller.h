#include "Common.h"
#include "Background.h"
#include "PlayerDef/Player.h"

#ifndef CONTROLLER
#define CONTROLLER

typedef struct controller_t{
    background_p* background;
    player_p* player;
    sdl_p* sdlSystem;
} controller_p;

void initController(controller_p* controller,player_p* player, sdl_p* sdlSystem, background_p* background);
void destructController(controller_p* controller);
stack* getView(controller_p* controller, int layer);
int runController(controller_p* controller);

#endif