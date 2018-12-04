#include "Controller.h"
#include "../MemManagement.h"
#include "../SDLInternals.h"
#include <stdlib.h>
#include <stdio.h>

int processKeys(controller_p* controller,stack* keysPressed);

void initController(controller_p* controller,player_p* player, room_p* room, sdl_p* sdlSystem, background_p* background){
    controller->player = player;
    controller->room = room;
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
    
    coordinates_p* center = getPlayerCoordinates(controller->player);
    stack* roomViews = getRoomView(controller->room, layer, center);
    stack* playerViews = getPlayerView(controller->player, layer);
    
    returnStack = combineStacks(playerViews, returnStack);
    returnStack = combineStacks(roomViews, returnStack);
    
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
