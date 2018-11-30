#include <stdio.h>
#include <stdlib.h>
#include "PlayerAnimation.h" 
#include "../Common.h"

void initAnimation(player_animation_p* animation, int numFrames, int columnMult, int rowMult){
    animation->numFrames = numFrames;
    animation->currentFrame = 0;
    animation->columnMult = columnMult;
    animation->rowMult = rowMult;    
    animation->frames = w_malloc(numFrames*sizeof(frame_p*));
}

void destructAnimation(player_animation_p* animation){
    int i=0;
    for(i=0; i < animation->numFrames; i++){
        w_free(animation->frames[i]);
    }
    w_free(animation->frames);
}

void addFrame(player_animation_p* animation, int spriteColumn, int spriteRow, int order){
    if(order >= 0 && order < animation->numFrames){
        animation->frames[order] = w_malloc(sizeof(frame_p));
        initFrame(animation->frames[order], animation->columnMult*spriteColumn, animation->rowMult*spriteRow);
    }
}

void updateAnimation(player_animation_p* animation){
    animation->currentFrame = ((animation->currentFrame)+1)%(animation->numFrames);
    printf("Current Frame: %d\n",animation->currentFrame);
}

frame_p* getCurrentFrame(player_animation_p* animation){
    return animation->frames[animation->currentFrame];
}