#include "Common.h"
#include "RoomTileCollection.h"

typedef struct room_t{
    images_p* imageBank;
    int imageBank;
    RoomTileCollection* roomTileCollection;
    coordinates_p* focus;          
}room_p;

void initRoom(room_p* room, images_p* imageBank);
void destructRoom(room_p* room);
stack* getRoomView(room_p* room, int layer);