#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include "Common.h"
#include "SDLInternals.h"
#include "WindowDef/Window.h"
#include "ControllerDef/Controller.h"
#include "RoomDef/Room.h"
#include "PlayerDef/Player.h"
#include "ImageBankDef/ImageBank.h"
#include "BackgroundDef/Background.h"
#include "ConfigDef/Config.h"
#include "MailSystemDef/MailSystem.h"

typedef struct gamestate_t{
    window_p* window;
    sdl_p* sdlSystem;
    controller_p* controller;
    images_p* imageBank;
    player_p* player;
    background_p* background;
    room_p* room;
    config_p* config;
    mailsystem_p* mailSystem;
}gamestate_p;

void runGame(gamestate_p* gameState);
gamestate_p* initializeSystems(char* configFile);
images_p* buildImageBank();
sdl_p* buildSdlSystem();
config_p* buildConfig(char* configFile);
background_p* buildBackground(images_p* imageBank);
controller_p* buildController(gamestate_p* gamestate);
window_p* buildWindow(sdl_p* sdlSystem, controller_p* controller, images_p* imageBank, mailsystem_p* mailSystem, background_p* background);
void destructGameState(gamestate_p* gameState);
gamestate_p* evaluateGameState(gamestate_p* gameState);
pthread_t* runThreads(gamestate_p* gameState);
void stopThreads(pthread_t* thread_ids, gamestate_p* gameState);
mailsystem_p* buildMailSystem();

int main(int argc, char* argv[]){
    freopen( "output.txt", "w", stdout );
    clock_t start, end;

    gamestate_p* gameState = initializeSystems("config/master.txt");
    pthread_t* threadIds = runThreads(gameState);
    runGame(gameState);

    stopThreads(threadIds, gameState);
    destructGameState(gameState);
    exit(0);
}

void runGame(gamestate_p* gameState){
    int quit = 0;
    clock_t start, end;
    while(quit == 0){
        start = clock();
        usleep(10000);
        quit = runController(gameState->controller);
        end = clock();
        printf("  Game Loop, time=%g \n",1000*((double)(end-start))/CLOCKS_PER_SEC);
    }
}

pthread_t* runThreads(gamestate_p* gameState){
    pthread_t* thread_ids = (pthread_t*) w_malloc(sizeof(pthread_t) * sizeof(gamestate_p));
    pthread_create(thread_ids, NULL, runWindow, (void*)gameState->window);
    return thread_ids;
}

void stopThreads(pthread_t* thread_ids, gamestate_p* gameState){
	blastFlag(gameState->mailSystem, STOP_THREADS_MESSAGE);
    pthread_join(thread_ids[0], NULL);
    w_free(thread_ids);
}

gamestate_p* initializeSystems(char* configFile){
    gamestate_p* gameState = w_malloc(sizeof(gamestate_p));
    
    gameState->mailSystem = buildMailSystem();
    gameState->imageBank = buildImageBank();
    gameState->config = buildConfig(configFile);
    gameState->sdlSystem = buildSdlSystem();
    gameState->player = buildPlayer(gameState->imageBank, gameState->config);
    gameState->room = buildRoom(gameState->imageBank, gameState->config);
    gameState->background = buildBackground(gameState->imageBank);
    gameState->controller = buildController(gameState);
    gameState->window = buildWindow(gameState->sdlSystem, gameState->controller, gameState->imageBank, gameState->mailSystem, gameState->background);
    
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

mailsystem_p* buildMailSystem(){
	mailsystem_p* mailSystem = w_malloc(sizeof(mailsystem_p));
	initMailSystem(mailSystem);
	return mailSystem;
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

controller_p* buildController(gamestate_p* gameState){
    controller_p* controller = w_malloc(sizeof(controller_p));
    initController(controller, gameState->player, gameState->room, gameState->sdlSystem, gameState->mailSystem);
    return controller;
}

window_p* buildWindow(sdl_p* sdlSystem, controller_p* controller, images_p* imageBank, mailsystem_p* mailSystem, background_p* background){
    window_p* window = w_malloc(sizeof(window_p));
    initWindow(window, sdlSystem, controller, imageBank, mailSystem, background);
    return window;
}
