#include "Controller.h"
#include "../MemManagement.h"
#include "../SDLInternals.h"
#include <stdlib.h>
#include <stdio.h>

int processKeys(controller_p* controller,stack* keysPressed);

void initController(controller_p* controller,player_p* player, room_p* room, sdl_p* sdlSystem, mailsystem_p* mailSystem){
    controller->player = player;
    controller->room = room;
    controller->sdlSystem = sdlSystem;
    controller->mailSystem = mailSystem;
    controller->mailAddress = WINDOW_ADDR;
    subscribeForMail(mailSystem, controller->mailAddress, constructMailbox());
}
void destructController(controller_p* controller){
}

int runController(controller_p* controller){
	int i;
    for(i = 0; i < LAYERS; i++){
    	sendViews(controller, i);
    }
    return processKeys(controller, getKeyStateCommand());
}

void sendViews(controller_p* controller, int layer){
    stack* returnStack = NULL;
    
    coordinates_p* center = getPlayerCoordinates(controller->player);
    stack* roomViews = getRoomView(controller->room, layer, center);
    stack* playerViews = getPlayerView(controller->player, layer);
    
    returnStack = playerViews;
    returnStack = combineStacks(roomViews, returnStack);
    
    foreach(envelopeMailStack(returnStack, WINDOW_ADDR), controller->mailSystem, sendMail);
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
