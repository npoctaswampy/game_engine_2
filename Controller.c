#include "Controller.h"
#include "MemManagement.h"
#include "SDLInternals.h"
#include <stdlib.h>
#include <stdio.h>

int processKeys(controller_p* controller,stack* keysPressed);

void initController(controller_p* controller,player_p* player, sdl_p* sdlSystem, background_p* background){
    controller->player = player;
    controller->sdlSystem = sdlSystem;
    controller->background = background;
}
void destructController(controller_p* controller){
}

int runController(controller_p* controller){
    return processKeys(controller,getKeyStateCommand());
}

stack* getView(controller_p* controller, int layer){
    stack* returnStack = NULL;
    if(layer==0) returnStack = getBackgroundView(controller->background);
    
    stack* playerCoords = getPlayerView(controller->player, layer);
    returnStack = combineStacks(playerCoords, returnStack);
    
    return returnStack;
}

int processKeys(controller_p* controller,stack* keysPressed){
    key* k = NULL;
    int quit = 0;
    
    if(keysPressed == NULL){
        playerProcessKey(controller->player,NONE);
    }
    
    while((k=pop_stack(&keysPressed)) != NULL){
        if(*k == ESCAPE) quit = 1;
        playerProcessKey(controller->player,*k);
        w_free(k);
    }
    freeStack(keysPressed);
    return quit;
}
