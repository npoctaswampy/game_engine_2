#include <stdio.h>
#include <stdlib.h>
#include "Animation.h" 
#include "../Common.h"

void initAnimation(animation_p* animation, int numFrames, int columnMult, int rowMult, int framesPerUpdate){
    animation->numFrames = numFrames;
    animation->currentFrame = 0;
    animation->columnMult = columnMult;
    animation->rowMult = rowMult;
    animation->framesPerUpdate = framesPerUpdate;
    animation->framesSinceUpdate = 0;
    animation->frames = w_malloc(numFrames*sizeof(frame_p*));
}

void destructAnimation(animation_p* animation){
    int i=0;
    for(i=0; i < animation->numFrames; i++){
        w_free(animation->frames[i]);
    }
    w_free(animation->frames);
}

void addFrame(animation_p* animation, int spriteColumn, int spriteRow, int order){
    if(order >= 0 && order < animation->numFrames){
        animation->frames[order] = w_malloc(sizeof(frame_p));
        initFrame(animation->frames[order], animation->columnMult*spriteColumn, animation->rowMult*spriteRow);
    }
}

void updateAnimation(animation_p* animation){
    animation->framesSinceUpdate = ((animation->framesSinceUpdate)+1)%(animation->framesPerUpdate);
    if(animation->framesSinceUpdate == 0)
        animation->currentFrame = ((animation->currentFrame)+1)%(animation->numFrames);
}

frame_p* getCurrentFrame(animation_p* animation){
    return animation->frames[animation->currentFrame];
}