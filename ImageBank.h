#include "Common.h"
#include "SDLInternals.h"

#ifndef IMAGEBANK
#define IMAGEBANK

#define TABLE_SIZE 20
#define MAX_ID 500

typedef struct images_t{
    table_t* imageTable;
}images_p;

void initTable(images_p* images);
void destructTable(images_p* images);
int saveImage(images_p* images, char* filename);
void deleteImage(images_p* images, int id);
SDL_Surface* retrieveImage(images_p* images, int id);

#endif