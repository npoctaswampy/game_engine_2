#include "Room.h"

char* getRoomSpriteFileName();
void fillRoomTiles(room_p* room);

void initRoom(room_p* room, images_p* imageBank){
    room->imageBank = imageBank;
    room->imageId = saveImage(room->imageBank, getRoomSpriteFileName());
    fillRoomTiles(room);
}

void destructRoom(room_p* room){
    
}

stack* getRoomView(room_p* room, int layer){
    
}

/* Initialization Functions
 * All of these should be replaced when config files are finalized. 
 */

char* getRoomSpriteFileName(){
    return "../sprites/textures2.bmp"
}

void fillRoomTiles(room_p* room){
    
}