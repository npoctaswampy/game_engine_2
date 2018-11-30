#include "Common.h"
#include "ImageBank.h"

#ifndef BACKGROUND
#define BACKGROUND

typedef struct background_t{
    int imageId;
    images_p* imageBank;
    coordinates_p* coords;
}background_p;

void initBackground(background_p* background, images_p* imageBank);
void destructBackground(background_p* background);
stack* getBackgroundView(background_p* background);

#endif