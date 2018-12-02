#include "../Common.h"
#include "../ImageBank.h"
#include "PlayerAnimation.h" 

#ifndef PLAYER
#define PLAYER


typedef struct player_t{
    int imageId;
    images_p* imageBank;
    coordinates_p* coords;
    int height;
    int width;
    int speed;
    player_animation_p** animations;
    int numberOfAnimates;
    int crntAnimateIndex;
    int upAnimateIndex;
    int downAnimateIndex;
    int leftAnimateIndex;
    int rightAnimateIndex;
    int actAnimateIndex;
    int idleAnimation;
}player_p;

void initPlayer(player_p* player, images_p* imageBank);
void destructPlayer(player_p* player);
stack* getPlayerView(player_p* player, int layer);
coordinates_p* getPlayerCoordinates(player_p* player);
void playerProcessKey(player_p* player,int k);

#endif