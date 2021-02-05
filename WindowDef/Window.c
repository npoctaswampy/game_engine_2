#include <stdio.h>
#include <stdlib.h>
#include "../Common.h"
#include "Window.h"

void processAndDrawViews(window_p* window, stack* views);
void drawView(window_p* window, view_p* view);

void initWindow(window_p* window, sdl_p* sdlSystem, controller_p* controller, images_p* imageBank, mailsystem_p* mailSystem, background_p* background){
    window->sdlSystem = sdlSystem;
    window->controller = controller;
    window->imageBank = imageBank;
    window->mailSystem = mailSystem;
    window->mailAddress = WINDOW_ADDR;
    window->background = background;
    subscribeForMail(mailSystem, window->mailAddress, constructMailbox());
}

void runWindow(void* window){
    window_p* _window = (window_p*) window;
    int i; stack* views = NULL;
    while(1){
        usleep(10000);
        printf("Getting mail...\n");
		views = emptyMail(_window->mailSystem, _window->mailAddress);
        printf("Done getting mail...\n");
        if(views != NULL){
			processAndDrawViews(_window, views);
			flipPage(_window->sdlSystem);
        }
    }
}

void processAndDrawViews(window_p* window, stack* views){
	message_p* view = NULL;
	drawView(window, getBackgroundView(window->background)->data);
    while((view = (message_p*) pop_stack(&views)) != NULL){
        drawView(window, view->optObj);
    }
}

void drawView(window_p* window, view_p* view){
    SDL_Surface* image = retrieveImage(window->imageBank, view->imageId);
    drawToScreen(view->coordinates, window->sdlSystem, image);
    w_free(view);
}
