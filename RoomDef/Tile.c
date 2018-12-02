#include "Tile.h"

void initTile(tile_p* tile, coordinates_p* coords){
    tile->coords = coords;
}

void destructTile(tile_p* tile){
    w_free(tile->coords);
}

coordinates_p* getTileCoords(tile_p* tile){
    return tile->coords;
}