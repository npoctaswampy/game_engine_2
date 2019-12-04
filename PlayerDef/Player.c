#include "Player.h"
#include "../Animation/Frame.h"

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

void fillFrames(const player_p *player, StringDict_p* animDict, int index);

/*Public Function Declarations*/

player_p* buildPlayer(images_p* imageBank, config_p* config){
    char* playerConfigFile = getStringFromDict(config->dict, "playerConfigFile");
    player_p* player = w_malloc(sizeof(player_p));
    initPlayer(player, imageBank, playerConfigFile);
    return player;    
}

void initPlayer(player_p* player, images_p* imageBank, char* playerConfigFile){
    player->playerConf = NULL;
    player->playerConf = (config_p*) malloc(sizeof(config_p));
    initConfig(player->playerConf);
    buildConfigFromFile(player->playerConf, playerConfigFile, 0);
    player->imageBank = imageBank;
    player->imageId = saveImage(player->imageBank, getPlayerSpriteFileName(player->playerConf));
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

char* getPlayerSpriteFileName(config_p* config){
    return getStringFromDict(config->dict, "sprite_sheet_player");
}

void fillPlayerSize(player_p* player){
    config_p* playerConf = player->playerConf;
    StringDict_p* playerDict = playerConf->dict;
    player->height = getIntFromDict(playerDict, "height");
    player->width = getIntFromDict(playerDict, "width");
}

void fillPlayerAnimations(player_p* player){
    fillPlayerAnimationParams(player);

    config_p* playerConf = player->playerConf;
    StringDict_p* playerDict = playerConf->dict;
    sdNode_p* animDictNode;
    StringDict_p* animDict;
    int index,animateSpeed,numFrames;

    LinkedList_p* animations = getLinkedListFromDict(playerDict, "animations");
    LinkedListNode_p* current = getHeadLLNode(animations);

    while(current != NULL){
        animDictNode = (sdNode_p*) current->data;
        animDict = (StringDict_p*) animDictNode->data;
        index = getIntFromDict(animDict,"index");
        animateSpeed = getIntFromDict(animDict,"animate_speed");
        numFrames = getIntFromDict(animDict,"num_frames");

        initAnimation(player->animations[index], numFrames, player->width, player->height,animateSpeed);
        fillFrames(player, animDict, index);

        current = current->next;
    }
    
    player->crntAnimateIndex = player->idleAnimation;
}

void fillFrames(const player_p *player, StringDict_p* animDict, int index) {
    sdNode_p* frameDictNode;
    StringDict_p *frameDict;
    int spriteCol,spriteRow,order;

    LinkedList_p *frames = getLinkedListFromDict(animDict, "frames");
    LinkedListNode_p *fCurrent = getHeadLLNode(frames);

    while (fCurrent != NULL) {
        frameDictNode = (sdNode_p *) fCurrent->data;
        frameDict = (StringDict_p *) frameDictNode->data;
        spriteCol = getIntFromDict(frameDict, "sprite_col");
        spriteRow = getIntFromDict(frameDict, "sprite_row");
        order = getIntFromDict(frameDict, "order");
        addFrame(player->animations[index], spriteCol, spriteRow, order);

        fCurrent = fCurrent->next;
    }
}

void fillPlayerAnimationParams(player_p* player){
    config_p* playerConf = player->playerConf;
    StringDict_p* playerDict = playerConf->dict;
    player->numberOfAnimates = getIntFromDict(playerDict, "number_of_animates");
    player->animations = w_malloc(player->numberOfAnimates*sizeof(animation_p*));
    int i;
    for(i=0; i<player->numberOfAnimates; i++){
        player->animations[i] = NULL;
    }
    player->upAnimateIndex = getIntFromDict(playerDict, "up_animate_index");
    player->downAnimateIndex = getIntFromDict(playerDict, "down_animate_index");
    player->leftAnimateIndex = getIntFromDict(playerDict, "left_animate_index");
    player->rightAnimateIndex = getIntFromDict(playerDict, "right_animate_index");
    player->idleAnimation = getIntFromDict(playerDict, "idle_animate_index");
    player->moveSpeed = getIntFromDict(playerDict, "travel_speed");

    player->animations[player->upAnimateIndex] = w_malloc(sizeof(animation_p));
    player->animations[player->downAnimateIndex] = w_malloc(sizeof(animation_p));
    player->animations[player->leftAnimateIndex] = w_malloc(sizeof(animation_p));
    player->animations[player->rightAnimateIndex] = w_malloc(sizeof(animation_p));
    player->animations[player->idleAnimation] = w_malloc(sizeof(animation_p));
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
            player->coords->mapY-=player->moveSpeed;
            break;
        case DOWN:
            player->coords->mapY+=player->moveSpeed;
            break;
        case LEFT:
            player->coords->mapX-=player->moveSpeed;
            break;
        case RIGHT:
            player->coords->mapX+=player->moveSpeed;
            break;   
    }
}