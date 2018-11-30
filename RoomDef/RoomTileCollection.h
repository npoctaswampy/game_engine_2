#include "Common.h"

typedef struct roomtilecollection_t{
    tile_p*** tiles;
    int numberOfTiles;
    int tiles_x;
    int tiles_y;
}rtc_p;

void initRoomTileCollection(rtc_p* roomTileCollection);
void destructRoomTileCollection(rtc_p* roomTileCollection);
void addTile(coordinates_p* coords);
void getTile(int x, int y, int layer);