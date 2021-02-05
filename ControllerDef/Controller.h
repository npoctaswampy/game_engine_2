#include "../Common.h"
#include "../PlayerDef/Player.h"
#include "../RoomDef/Room.h"
#include "../MailSystemDef/MailSystem.h"

#ifndef CONTROLLER
#define CONTROLLER

typedef struct controller_t{
    player_p* player;
    room_p* room;
    sdl_p* sdlSystem;
    mailsystem_p* mailSystem;
    char* mailAddress;
} controller_p;

void initController(controller_p* controller,player_p* player, room_p* room, sdl_p* sdlSystem, mailsystem_p* mailSystem);
void destructController(controller_p* controller);
stack* getView(controller_p* controller, int layer);
int runController(controller_p* controller);

#endif
