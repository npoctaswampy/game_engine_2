#include "ImageBank.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initTable(images_p* images){
    srand(time(NULL));
    images->imageTable = table_construct(TABLE_SIZE, LINEAR);
}

void destructTable(images_p* images){
    table_destruct(images->imageTable);
}

int saveImage(images_p* images, char* filename){
    hashkey_t id = (hashkey_t) rand()%MAX_ID;
    SDL_Surface* surface = getSurfaceFromFile(filename);
    table_insert(images->imageTable, id, surface);
    return id;
}

void deleteImage(images_p* images, int id){
    SDL_Surface* surface = table_delete(images->imageTable, (hashkey_t) id);
    freeSDLSurface(surface);
}

SDL_Surface* retrieveImage(images_p* images, int id){
    return (SDL_Surface*) table_retrieve(images->imageTable, (hashkey_t) id);
}

