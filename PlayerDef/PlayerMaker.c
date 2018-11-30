#include "Player.h"

void fillPlayerCoords(player_p* player);
char* getPlayerSpriteFileName();
void fillPlayerSize(player_p* player);

void initPlayer(player_p* player, images_p* imageBank){
    player->imageBank = imageBank;
    player->imageId = saveImage(player->imageBank, getPlayerSpriteFileName());
    fillPlayerSize(player);
    fillPlayerCoords(player);
}

void destructPlayer(player_p* player){
    deleteImage(player->imageBank, player->imageId);
}

stack* getPlayerView(player_p* player, int layer){
    stack* s = NULL;
    if(layer == 1){
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
            player->coords->srcX = player->width * 6;
            break;
        case DOWN:
            player->coords->srcX = player->width * 0;
            break;
        case LEFT:
            player->coords->srcX = player->width * 3;
            break;
        case RIGHT:
            player->coords->srcX = player->width * 9;
            break;    
    }
}

void fillPlayerCoords(player_p* player){
    player->coords = w_malloc(sizeof(coordinates_p));
    player->coords->srcX = 0;
    player->coords->srcY = 0; 
    player->coords->srcW = player->width; 
    player->coords->srcH = player->height; 
    player->coords->destX = 
            (SCREEN_WIDTH-(player->width/2))/2;
    player->coords->destY = 
            (SCREEN_HEIGHT-(player->height/2))/2;
    player->coords->destW = player->width;
    player->coords->destH = player->height;
}

char* getPlayerSpriteFileName(){
    return "../sprites/sprite_sheet_boy.bmp";
}

void fillPlayerSize(player_p* player){
    player->height = 64;
    player->width = 64;
}
