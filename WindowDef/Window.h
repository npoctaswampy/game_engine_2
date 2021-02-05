#include "../SDLInternals.h"
#include "../ControllerDef/Controller.h"
#include "../ImageBankDef/ImageBank.h"
#include "../MailSystemDef/MailSystem.h"
#include "../BackgroundDef/Background.h"

#ifndef WINDOW
#define WINDOW

typedef struct window_t{
    sdl_p* sdlSystem;
    controller_p* controller;
    images_p* imageBank;
    mailsystem_p* mailSystem;
    background_p* background;
    char* mailAddress;
} window_p;

void initWindow(window_p* window, sdl_p* sdlSystem, controller_p* controller, images_p* imageBank, mailsystem_p* mailSystem, background_p* background);
void runWindow(void* window);

#endif
