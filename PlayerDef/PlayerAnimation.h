#include "Frame.h"

#ifndef PLAYERANIM
#define PLAYERANIM

typedef struct player_animation_t{
    int numFrames;
    int currentFrame;
    int columnMult;
    int rowMult;
    frame_p** frames;
}player_animation_p;

void initAnimation(player_animation_p* animation, int numFrames, int columnMult, int rowMult);
void destructAnimation(player_animation_p* animation);
void addFrame(player_animation_p* animation, int spriteColumn, int spriteRow, int order);
void updateAnimation(player_animation_p* animation);
frame_p* getCurrentFrame(player_animation_p* animation);

#endif