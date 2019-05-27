#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "SDLInternals.h"
#include "WindowDef/Window.h"
#include "ControllerDef/Controller.h"
#include "RoomDef/Room.h"
#include "PlayerDef/Player.h"
#include "ImageBankDef/ImageBank.h"
#include "BackgroundDef/Background.h"
#include "ConfigDef/Config.h"

typedef struct gamestate_t{
    window_p* window;
    sdl_p* sdlSystem;
    controller_p* controller;
    images_p* imageBank;
    player_p* player;
    background_p* background;
    room_p* room;
    config_p* config;
}gamestate_p;

void runGame(gamestate_p* gameState);
gamestate_p* initializeSystems(char* configFile);
images_p* buildImageBank();
sdl_p* buildSdlSystem();
config_p* buildConfig(char* configFile);
background_p* buildBackground(images_p* imageBank);
controller_p* buildController(player_p* player, room_p* room, sdl_p* sdlSystem, background_p* background);
window_p* buildWindow(sdl_p* sdlSystem, controller_p* controller, images_p* imageBank);
void destructGameState(gamestate_p* gameState);
gamestate_p* evaluateGameState(gamestate_p* gameState);

int main(int argc, char* argv[]){
    if(argc > 1){
        gamestate_p* gameState = initializeSystems(argv[1]);
        runGame(gameState);
        destructGameState(gameState);
        exit(0);
    }else{
        printf("No config file specified. Exiting...\n");
        return 0;
    }
}

void runGame(gamestate_p* gameState){
    int quit = 0;
    while(quit == 0){
        usleep(10000);
        runWindow(gameState->window);
        quit = runController(gameState->controller);
    }
}

gamestate_p* initializeSystems(char* configFile){
    gamestate_p* gameState = w_malloc(sizeof(gamestate_p));
    
    gameState->imageBank = buildImageBank();
    gameState->config = buildConfig(configFile);
    gameState->sdlSystem = buildSdlSystem(gameState->imageBank);
    gameState->player = buildPlayer(gameState->imageBank, gameState->config);
    gameState->room = buildRoom(gameState->imageBank, gameState->config);
    gameState->background = buildBackground(gameState->imageBank);
    gameState->controller = buildController(gameState->player, gameState->room, gameState->sdlSystem, gameState->background);
    gameState->window = buildWindow(gameState->sdlSystem, gameState->controller, gameState->imageBank);
    
    return evaluateGameState(gameState);
}

gamestate_p* evaluateGameState(gamestate_p* gameState){
    if(gameState->config->dict == NULL) return NULL;
    if(gameState->imageBank == NULL) return NULL;
    if(gameState->sdlSystem == NULL) return NULL;
    if(gameState->player == NULL) return NULL;
    if(gameState->room == NULL) return NULL;
    if(gameState->background == NULL) return NULL;
    if(gameState->controller == NULL) return NULL;
    if(gameState->window == NULL) return NULL;
    return gameState;
}

void destructGameState(gamestate_p* gameState){
    destructPlayer(gameState->player);
    destructRoom(gameState->room);
    destructBackground(gameState->background);
    destructController(gameState->controller);
    destructTable(gameState->imageBank);
    destructConfig(gameState->config);
    teardownSDL(gameState->sdlSystem);
    
    w_free(gameState->player);
    w_free(gameState->room);
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

config_p* buildConfig(char* configFile){
    config_p* config = malloc(sizeof(config_p));
    initConfig(config);
    buildConfigFromFile(config, configFile, 0);
    return config;
}

background_p* buildBackground(images_p* imageBank){
    background_p* background = w_malloc(sizeof(background_p));
    initBackground(background, imageBank);
    return background; 
}

controller_p* buildController(player_p* player, room_p* room, sdl_p* sdlSystem, background_p* background){
    controller_p* controller = w_malloc(sizeof(controller_p));
    initController(controller, player, room, sdlSystem, background);
    return controller;
}

window_p* buildWindow(sdl_p* sdlSystem, controller_p* controller, images_p* imageBank){
    window_p* window = w_malloc(sizeof(window_p));
    initWindow(window, sdlSystem, controller, imageBank);
    return window;
}