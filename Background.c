#include <stdio.h>
#include <stdlib.h>
#include "Background.h"

void fillBackgroundCoords(background_p* background);

void initBackground(background_p* background, images_p* imageBank){
    background->imageBank = imageBank;
    background->imageId = saveImage(background->imageBank, "../sprites/background.bmp");
    fillBackgroundCoords(background);
}

void destructBackground(background_p* background){
    deleteImage(background->imageBank, background->imageId);
    w_free(background->coords);
}

stack* getBackgroundView(background_p* background){
    stack* s = NULL;
    view_p* view = w_malloc(sizeof(view_p));
    view->coordinates = background->coords;
    view->imageId = background->imageId;
    push_stack(&s, view);
    return s;
}

void fillBackgroundCoords(background_p* background){
    background->coords = w_malloc(sizeof(coordinates_p));
    background->coords->srcX = 0;
    background->coords->srcY = 0; 
    background->coords->srcW = SCREEN_WIDTH; 
    background->coords->srcH = SCREEN_HEIGHT; 
    background->coords->destX = 0;
    background->coords->destY = 0;
    background->coords->destW = SCREEN_WIDTH;
    background->coords->destH = SCREEN_HEIGHT;    
}