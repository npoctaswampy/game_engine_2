#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "SDLInternals.h"
#include "Window.h"
#include "Controller.h"
#include "PlayerDef/Player.h"
#include "ImageBank.h"
#include "Background.h"

typedef struct gamestate_t{
    window_p* window;
    sdl_p* sdlSystem;
    controller_p* controller;
    images_p* imageBank;
    player_p* player;
    background_p* background;
}gamestate_p;

void runGame(gamestate_p* gameState);
gamestate_p* initializeSystems();
images_p* buildImageBank();
sdl_p* buildSdlSystem();
player_p* buildPlayer(images_p* imageBank);
background_p* buildBackground(images_p* imageBank);
controller_p* buildController(player_p* player, sdl_p* sdlSystem, background_p* background);
window_p* buildWindow(sdl_p* sdlSystem, controller_p* controller, images_p* imageBank);
void destructGameState(gamestate_p* gameState);

int main(){
    gamestate_p* gameState = initializeSystems();
    runGame(gameState);
    destructGameState(gameState);
    exit(0);
}

void runGame(gamestate_p* gameState){
    int quit = 0;
    while(quit == 0){
        usleep(10000);
        runWindow(gameState->window);
        quit = runController(gameState->controller);
    }
}

gamestate_p* initializeSystems(){
    gamestate_p* gameState = w_malloc(sizeof(gamestate_p));
    
    gameState->imageBank = buildImageBank();
    gameState->sdlSystem = buildSdlSystem(gameState->imageBank);
    gameState->player = buildPlayer(gameState->imageBank);
    gameState->background = buildBackground(gameState->imageBank);
    gameState->controller = buildController(gameState->player, gameState->sdlSystem, gameState->background);
    gameState->window = buildWindow(gameState->sdlSystem, gameState->controller, gameState->imageBank);
    
    return gameState;
}

void destructGameState(gamestate_p* gameState){
    destructPlayer(gameState->player);
    destructBackground(gameState->background);
    destructController(gameState->controller);
    destructTable(gameState->imageBank);
    teardownSDL(gameState->sdlSystem);
    
    w_free(gameState->player);
    w_free(gameState->background);
    w_free(gameState->controller);
    w_free(gameState->imageBank);
    w_free(gameState->sdlSystem);
    w_free(gameState->window);
    w_free(gameState);
}

images_p* buildImageBank(){
    images_p* images = w_malloc(sizeof(images_p));
    initTable(images);
    return images;
}

sdl_p* buildSdlSystem(){
    sdl_p* sdlSystem = (sdl_p*) w_malloc(sizeof(sdl_p));
    initializeSDL(sdlSystem);
    return sdlSystem;
}

player_p* buildPlayer(images_p* imageBank){
    player_p* player = w_malloc(sizeof(player_p));
    initPlayer(player, imageBank);
    return player;    
}

background_p* buildBackground(images_p* imageBank){
    background_p* background = w_malloc(sizeof(background_p));
    initBackground(background, imageBank);
    return background; 
}

controller_p* buildController(player_p* player, sdl_p* sdlSystem, background_p* background){
    controller_p* controller = w_malloc(sizeof(controller_p));
    initController(controller, player, sdlSystem, background);
    return controller;
}

window_p* buildWindow(sdl_p* sdlSystem, controller_p* controller, images_p* imageBank){
    window_p* window = w_malloc(sizeof(window_p));
    initWindow(window, sdlSystem, controller, imageBank);
    return window;
}