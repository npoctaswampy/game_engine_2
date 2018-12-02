#include "../Common.h"
#include "../ImageBank.h"
#include "RoomTileCollection.h"

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
}room_p;

void initRoom(room_p* room, images_p* imageBank);
void destructRoom(room_p* room);
stack* getRoomView(room_p* room, int layer, coordinates_p* center);

#endif