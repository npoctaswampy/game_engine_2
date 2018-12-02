#include "../Common.h"

#ifndef TILE
#define TILE

typedef struct tile_t{
    coordinates_p* coords;
}tile_p;

void initTile(tile_p* tile,coordinates_p* coords);
void destructTile(tile_p* tile);
coordinates_p* getTileCoords(tile_p* tile);

#endif