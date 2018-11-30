#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "ImageBank.h"


/*
 * 
 */
int main() {
    //sdl_p* sdlSystem = (sdl_p*) w_malloc(sizeof(sdlSystem));
    //initializeSDL(sdlSystem);
    images_p* imageBank = (images_p*) w_malloc(sizeof(images_p));
    initTable(imageBank);
    int id1 = saveImage(imageBank, "../sprites/textures.bmp");
    int id2 = saveImage(imageBank, "../sprites/sprite_sheet_boy.bmp");
    SDL_Surface* image1 = retrieveImage(imageBank, id1);
    SDL_Surface* image2 = retrieveImage(imageBank, id2);
    if(image1 != NULL) printf("Retrieved image1 with id %d\n",id1);
    else printf("Did not retrieve image1 with id %d\n",id1);
    if(image2 != NULL) printf("Retrieved image2 with id %d\n",id2);
    else printf("Did not retrieve image2 with id %d\n",id2);
    
    deleteImage(imageBank, id1);
    deleteImage(imageBank, id2);
    destructTable(imageBank);
    w_free(imageBank);
}

