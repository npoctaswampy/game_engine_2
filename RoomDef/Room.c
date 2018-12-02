#include "Room.h"

char* getRoomSpriteFileName();
void fillRoomTiles(room_p* room);
viewParams_p getViewParams(coordinates_p* center, room_p* room, int layer);
void updateScreenLocation(coordinates_p* coords, coordinates_p* center);
void initRoomTileCollections(room_p* room);

void initRoom(room_p* room, images_p* imageBank){
    room->imageBank = imageBank;
    room->imageId = saveImage(room->imageBank, getRoomSpriteFileName());
    initRoomTileCollections(room);
    fillRoomTiles(room);
}

void destructRoom(room_p* room){
    deleteImage(room->imageBank, room->imageId);
}

stack* getRoomView(room_p* room, int layer, coordinates_p* center){
    int i,j;
    stack* s = NULL;
    viewParams_p vp = getViewParams(center, room, layer);
    for(i = vp.start_x; i < vp.end_x; i++){
        for(j = vp.start_y; j < vp.end_y; j++){
            view_p* view = w_malloc(sizeof(view_p));
            view->coordinates = getTileCollectionCoords(room->roomTileCollection[layer], i, j);
            if(view->coordinates != NULL){
                updateScreenLocation(view->coordinates, center);
                view->imageId = room->imageId;
                push_stack(&s, view);
            }else w_free(view);
        }
    }
    return s;
}

void updateScreenLocation(coordinates_p* coords, coordinates_p* center){
    int xDiff = coords->mapX - center->mapX;
    int yDiff = coords->mapY - center->mapY;
    coords->destX = center->destX + xDiff;
    coords->destY = center->destY + yDiff;
}

viewParams_p getViewParams(coordinates_p* center, room_p* room, int layer){
    viewParams_p vp;
    
    int upperX = getTileCollectionRows(room->roomTileCollection[layer])*TILESIZE;
    int upperY = getTileCollectionColumns(room->roomTileCollection[layer])*TILESIZE;
    
    vp.start_x = center->mapX - SCREEN_WIDTH;
    vp.end_x = center->mapX + SCREEN_WIDTH;
    vp.start_y = center->mapY - SCREEN_HEIGHT;
    vp.end_y = center->mapY + SCREEN_HEIGHT;
    
    vp.start_x = ((vp.start_x > 0) ? vp.start_x : 0) / TILESIZE;
    vp.end_x = ((vp.end_x < upperX) ? vp.end_x : upperX) / TILESIZE;
    vp.start_y = ((vp.start_y > 0) ? vp.start_y : 0) / TILESIZE;
    vp.end_y = ((vp.end_y < upperY) ? vp.end_y : upperY) / TILESIZE;
    return vp;
}

/* Initialization Functions
 * All of these should be replaced when config files are finalized. 
 */

char* getRoomSpriteFileName(){
    return "../sprites/textures2.bmp";
}

void initRoomTileCollections(room_p* room){
    int i;
    room->roomTileCollection = w_malloc(LAYERS*sizeof(rtc_p*));
    for(i = 0; i < LAYERS; i++){
        room->roomTileCollection[i] = w_malloc(sizeof(rtc_p));
        initRoomTileCollection(room->roomTileCollection[i], 100, 100);
    }
}

void fillRoomTiles(room_p* room){
    int i,j;
    int upperX = getTileCollectionRows(room->roomTileCollection[1]);
    int upperY = getTileCollectionColumns(room->roomTileCollection[1]);
    
    for(i=0; i < upperX; i++){
        for(j=0; j<upperY; j++){
            coordinates_p* coords = w_malloc(sizeof(coordinates_p));
            coords->srcX = 0;
            coords->srcY = 0; 
            coords->srcW = TILESIZE; 
            coords->srcH = TILESIZE; 
            coords->destW = TILESIZE;
            coords->destH = TILESIZE;
            coords->mapX = i*TILESIZE;
            coords->mapY = j*TILESIZE;
            coords->layer = 1;
            addTile(room->roomTileCollection[1], coords);
        }
    }
}
