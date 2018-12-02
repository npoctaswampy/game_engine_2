#include "../Common.h"
#include "Tile.h"

#ifndef RTC
#define RTC

#define TILESIZE 64

typedef struct roomtilecollection_t{
    tile_p*** tiles;
    int numberOfTiles;
    int tiles_x;
    int tiles_y;
}rtc_p;

void initRoomTileCollection(rtc_p* roomTileCollection, int tiles_x, int tiles_y);
void destructRoomTileCollection(rtc_p* roomTileCollection);
void addTile(rtc_p* roomTileCollection, coordinates_p* coords);
coordinates_p* getTileCollectionCoords(rtc_p* roomTileCollection, int x, int y);
int getTileCollectionRows(rtc_p* roomTileCollection);
int getTileCollectionColumns(rtc_p* roomTileCollection);

#endif