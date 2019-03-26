#include "../Common.h"
#include "../ImageBankDef/ImageBank.h"
#include "RoomTileCollection.h"
#include "../ConfigDef/Config.h"

#ifndef ROOM
#define ROOM

typedef struct viewParams_t{
    int start_x;
    int end_x;
    int start_y;
    int end_y;
}viewParams_p;

typedef struct room_t{
    images_p* imageBank;
    int imageId;
    rtc_p** roomTileCollection;
    coordinates_p* focus;
    config_p* roomConf;
}room_p;

room_p* buildRoom(images_p* imageBank,config_p* config);
void initRoom(room_p* room, images_p* imageBank, char* configFile);
void destructRoom(room_p* room);
stack* getRoomView(room_p* room, int layer, coordinates_p* center);

#endif