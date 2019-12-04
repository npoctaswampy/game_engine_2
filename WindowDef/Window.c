#include <stdio.h>
#include <stdlib.h>
#include "../Common.h"
#include "Window.h"

void processAndDrawViews(window_p* window, stack* views);
void drawView(window_p* window, view_p* view);

void initWindow(window_p* window, sdl_p* sdlSystem, controller_p* controller, images_p* imageBank){
    window->sdlSystem = sdlSystem;
    window->controller = controller;
    window->imageBank = imageBank;
}

void runWindow(void* window){
    window_p* _window = (window_p*) window;
    int i; stack* views = NULL;
    while(1){
        usleep(10000);
        for(i = 0; i < LAYERS; i++){
            views = getView(_window->controller, i);
            processAndDrawViews(_window, views);
        }
        flipPage(_window->sdlSystem);
    }
}

void processAndDrawViews(window_p* window, stack* views){
    view_p* view = NULL;
    while((view = (view_p*) pop_stack(&views) ) != NULL){
        drawView(window, view);
    }
}

void drawView(window_p* window, view_p* view){
    SDL_Surface* image = retrieveImage(window->imageBank, view->imageId);
    drawToScreen(view->coordinates, window->sdlSystem, image);
    w_free(view);
}