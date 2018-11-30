#include "RoomTileCollection.h"

void initRoomTileCollection(rtc_p* roomTileCollection, int tiles_x, int tiles_y){
    int i;
    roomTileCollection->tiles_x = tiles_x;
    roomTileCollection->tiles_y = tiles_y;
    roomTileCollection->tiles = w_malloc(tiles_x*sizeof(tile_p**));
    for(i=0; i<tiles_x; i++){
        roomTileCollection->tiles[i] = w_malloc(tiles_y*sizeof(tile_p**));
    }
}

void destructRoomTileCollection(rtc_p* roomTileCollection){
    int i;
    for(i=0; i<roomTileCollection->tiles_x; i++){
        roomTileCollection->tiles[i] = w_free(roomTileCollection->tiles_y*sizeof(tile_p**));
    }
    roomTileCollection->tiles = w_free(tiles_x*sizeof(tile_p**));
}

void addTile(rtc_p* roomTileCollection, coordinates_p* coords){
    
}

coordinates_p* getTileCoords(rtc_p* roomTileCollection, int x, int y, int layer){
    
}

int getTileCollectionRows(rtc_p* roomTileCollection){
    return roomTileCollection->tiles_x;
}

int getTileCollectionColumns(rtc_p* roomTileCollection){
    return roomTileCollection->tiles_y;w
    
}