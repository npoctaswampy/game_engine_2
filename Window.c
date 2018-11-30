#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "Window.h"

void processAndDrawViews(window_p* window, stack* views);
void drawView(window_p* window, view_p* view);

void initWindow(window_p* window, sdl_p* sdlSystem, controller_p* controller, images_p* imageBank){
    window->sdlSystem = sdlSystem;
    window->controller = controller;
    window->imageBank = imageBank;
}

void runWindow(window_p* window){
    int i;
    stack* views = NULL;
    for(i = 0; i < LAYERS; i++){
        views = getView(window->controller, i);
        processAndDrawViews(window, views);
    }
    flipPage(window->sdlSystem);
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