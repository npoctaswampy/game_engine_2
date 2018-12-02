#include "RoomTileCollection.h"

void initTileValues(tile_p*** tiles, int tiles_x, int tiles_y);

void initRoomTileCollection(rtc_p* roomTileCollection, int tiles_x, int tiles_y){
    int i;
    roomTileCollection->tiles_x = tiles_x;
    roomTileCollection->tiles_y = tiles_y;
    roomTileCollection->numberOfTiles = tiles_x*tiles_y;
    roomTileCollection->tiles = w_malloc(tiles_x*sizeof(tile_p**));
    for(i=0; i<tiles_x; i++){
        roomTileCollection->tiles[i] = w_malloc(tiles_y*sizeof(tile_p*));
    }
    initTileValues(roomTileCollection->tiles, tiles_x, tiles_y);    
}

void destructRoomTileCollection(rtc_p* roomTileCollection){
    int i,j;
    for(i=0; i<roomTileCollection->tiles_x; i++){
        for(j=0; j<roomTileCollection->tiles_x; j++){
            destructTile(roomTileCollection->tiles[i][j]);
            w_free(roomTileCollection->tiles[i][j]);
        }
        w_free(roomTileCollection->tiles[i]);
    }
    w_free(roomTileCollection->tiles);
}

void addTile(rtc_p* roomTileCollection, coordinates_p* coords){
    int x = coords->mapX/TILESIZE;
    int y = coords->mapY/TILESIZE;
    tile_p* oldTile = roomTileCollection->tiles[x][y];
    tile_p* newTile = w_malloc(sizeof(tile_p));
    initTile(newTile, coords);
    roomTileCollection->tiles[x][y] = newTile;
    if(oldTile != NULL) w_free(oldTile);
}

coordinates_p* getTileCollectionCoords(rtc_p* roomTileCollection, int x, int y){
    if(roomTileCollection->tiles[x][y] != NULL)
        return roomTileCollection->tiles[x][y]->coords;
    else return NULL;
}

int getTileCollectionRows(rtc_p* roomTileCollection){
    return roomTileCollection->tiles_x;
}

int getTileCollectionColumns(rtc_p* roomTileCollection){
    return roomTileCollection->tiles_y;    
}

void initTileValues(tile_p*** tiles, int tiles_x, int tiles_y){
    int i,j;
    for(i=0; i<tiles_x; i++){
        for(j=0; j<tiles_y; j++){
            tiles[i][j] = NULL;
        }
    }
}