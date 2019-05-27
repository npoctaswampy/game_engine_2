#include "../Common.h"
#include "../ImageBankDef/ImageBank.h"
#include "PlayerAnimation.h"
#include "../ConfigDef/Config.h"

#ifndef PLAYER
#define PLAYER

#define ANIMSPEED 4

typedef struct player_t{
    int imageId;
    config_p* playerConf;
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
    int moveSpeed;
}player_p;

player_p* buildPlayer(images_p* imageBank, config_p* config);
void initPlayer(player_p* player, images_p* imageBank, char* playerConfigFile);
void destructPlayer(player_p* player);
stack* getPlayerView(player_p* player, int layer);
coordinates_p* getPlayerCoordinates(player_p* player);
void playerProcessKey(player_p* player,int k);

#endif