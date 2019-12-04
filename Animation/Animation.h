#include "Frame.h"

#ifndef PLAYERANIM
#define PLAYERANIM

typedef struct animation_t{
    int numFrames;
    int currentFrame;
    int columnMult;
    int rowMult;
    int framesPerUpdate;
    int framesSinceUpdate;
    frame_p** frames;
}animation_p;

void initAnimation(animation_p* animation, int numFrames, int columnMult, int rowMult, int framesPerUpdate);
void destructAnimation(animation_p* animation);
void addFrame(animation_p* animation, int spriteColumn, int spriteRow, int order);
void updateAnimation(animation_p* animation);
frame_p* getCurrentFrame(animation_p* animation);

#endif