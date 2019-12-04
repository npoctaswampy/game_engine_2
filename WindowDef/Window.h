#include "../SDLInternals.h"
#include "../ControllerDef/Controller.h"
#include "../ImageBankDef/ImageBank.h"

#ifndef WINDOW
#define WINDOW

typedef struct window_t{
    sdl_p* sdlSystem;
    controller_p* controller;
    images_p* imageBank;
} window_p;

void initWindow(window_p* window, sdl_p* sdlSystem, controller_p* controller, images_p* imageBank);
void runWindow(void* window);

#endif