#include "Player.h"
#include "Frame.h"

/*Initialization Function Declarations*/
void fillPlayerCoords(player_p* player);
char* getPlayerSpriteFileName();
void fillPlayerSize(player_p* player);
void fillPlayerAnimations(player_p* player);
void fillPlayerAnimationParams(player_p* player);

/*Animation Helper Functions*/
void updateDirection(player_p* player, int directionAnimateIndex);
void updatePlayerToCurrentFrame(player_p* player);

/*Location Calculators*/
void updatePlayerLocation(player_p* player,int k);

/*Public Function Declarations*/

player_p* buildPlayer(images_p* imageBank){
    player_p* player = w_malloc(sizeof(player_p));
    initPlayer(player, imageBank);
    return player;    
}

void initPlayer(player_p* player, images_p* imageBank){
    player->imageBank = imageBank;
    player->imageId = saveImage(player->imageBank, getPlayerSpriteFileName());
    fillPlayerSize(player);
    fillPlayerAnimations(player);
    fillPlayerCoords(player);
    updatePlayerToCurrentFrame(player);
}

void destructPlayer(player_p* player){
    int i;
    for(i=0; i<player->numberOfAnimates; i++){
        if(player->animations[i] != NULL){
            destructAnimation(player->animations[i]);
            w_free(player->animations[i]);
        }
    }
    w_free(player->animations);
    deleteImage(player->imageBank, player->imageId);
    w_free(player->coords);
    
}

coordinates_p* getPlayerCoordinates(player_p* player){
    return player->coords;
}

stack* getPlayerView(player_p* player, int layer){
    stack* s = NULL;
    if(layer == player->coords->layer){
        updatePlayerToCurrentFrame(player);
        view_p* view = w_malloc(sizeof(view_p));
        view->coordinates = player->coords;
        view->imageId = player->imageId;
        push_stack(&s, view);
    }
    return s;
}

void playerProcessKey(player_p* player,int k){
    switch(k){
        case UP:
            updateDirection(player, player->upAnimateIndex);
            break;
        case DOWN:
            updateDirection(player, player->downAnimateIndex);
            break;
        case LEFT:
            updateDirection(player, player->leftAnimateIndex);
            break;
        case RIGHT:
            updateDirection(player, player->rightAnimateIndex);
            break;   
        case NONE:
            player->crntAnimateIndex = player->idleAnimation;
            break;
    }
    updatePlayerLocation(player, k);
}

/* Initialization Functions
 * All of these should be replaced when config files are finalized. 
 */

void fillPlayerCoords(player_p* player){
    player->coords = w_malloc(sizeof(coordinates_p));
    player->coords->srcW = player->width; 
    player->coords->srcH = player->height; 
    player->coords->destX = 
            (SCREEN_WIDTH/2)-(player->width/2);
    player->coords->destY = 
            (SCREEN_HEIGHT/2)-(player->height/2);
    player->coords->destW = player->width;
    player->coords->destH = player->height;
    player->coords->mapX = 0;
    player->coords->mapY = 0;
    player->coords->layer = 1;
}

char* getPlayerSpriteFileName(){
    return "../sprites/sprite_sheet_boy.bmp";
}

void fillPlayerSize(player_p* player){
    player->height = 64;
    player->width = 64;
}

void fillPlayerAnimations(player_p* player){
    fillPlayerAnimationParams(player);
    
    player->upAnimateIndex = 0;
    player->animations[player->upAnimateIndex] = w_malloc(sizeof(player_animation_p));
    initAnimation(player->animations[player->upAnimateIndex], 2, player->width, player->height,ANIMSPEED);
    addFrame(player->animations[player->upAnimateIndex], 7, 0, 0);
    addFrame(player->animations[player->upAnimateIndex], 8, 0, 1);
    
    player->downAnimateIndex = 1;
    player->animations[player->downAnimateIndex] = w_malloc(sizeof(player_animation_p));
    initAnimation(player->animations[player->downAnimateIndex], 2, player->width, player->height,ANIMSPEED);
    addFrame(player->animations[player->downAnimateIndex], 1, 0, 0);
    addFrame(player->animations[player->downAnimateIndex], 2, 0, 1);
    
    player->leftAnimateIndex = 2;
    player->animations[player->leftAnimateIndex] = w_malloc(sizeof(player_animation_p));
    initAnimation(player->animations[player->leftAnimateIndex], 3, player->width, player->height,ANIMSPEED);
    addFrame(player->animations[player->leftAnimateIndex], 3, 0, 0);
    addFrame(player->animations[player->leftAnimateIndex], 4, 0, 1);
    addFrame(player->animations[player->leftAnimateIndex], 5, 0, 2);
    
    player->rightAnimateIndex = 3;
    player->animations[player->rightAnimateIndex] = w_malloc(sizeof(player_animation_p));
    initAnimation(player->animations[player->rightAnimateIndex], 3, player->width, player->height,ANIMSPEED);
    addFrame(player->animations[player->rightAnimateIndex], 9, 0, 0);
    addFrame(player->animations[player->rightAnimateIndex], 10, 0, 1);
    addFrame(player->animations[player->rightAnimateIndex], 11, 0, 2);
    
    player->idleAnimation = 5;
    player->animations[player->idleAnimation] = w_malloc(sizeof(player_animation_p));
    initAnimation(player->animations[player->idleAnimation], 1, player->width, player->height,ANIMSPEED);
    addFrame(player->animations[player->idleAnimation], 0, 0, 0);
    
    player->crntAnimateIndex = player->idleAnimation;
}

void fillPlayerAnimationParams(player_p* player){
    player->numberOfAnimates = 10;
    player->animations = w_malloc(player->numberOfAnimates*sizeof(player_animation_p*));
    int i;
    for(i=0; i<player->numberOfAnimates; i++){
        player->animations[i] = NULL;
    }
}

/*Animation Helper Functions*/

void updateDirection(player_p* player, int directionAnimateIndex){
    player->crntAnimateIndex = directionAnimateIndex;
}

void updatePlayerToCurrentFrame(player_p* player){
    updateAnimation(player->animations[player->crntAnimateIndex]);
    frame_p* frame = getCurrentFrame(player->animations[player->crntAnimateIndex]);
    player->coords->srcX = frame->column;
    player->coords->srcY = frame->row;
}

/*Location Calculations*/

void updatePlayerLocation(player_p* player,int k){
    switch(k){
        case UP:
            player->coords->mapY-=8;
            break;
        case DOWN:
            player->coords->mapY+=8;
            break;
        case LEFT:
            player->coords->mapX-=8;
            break;
        case RIGHT:
            player->coords->mapX+=8;
            break;   
    }
}