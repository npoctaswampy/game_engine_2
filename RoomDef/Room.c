#include "Room.h"

char* getRoomSpriteFileName();
void fillRoomTiles(room_p* room);
viewParams_p getViewParams(coordinates_p* center, room_p* room, int layer);
void updateScreenLocation(coordinates_p* coords, coordinates_p* center);
void initRoomTileCollections(room_p* room);

room_p* buildRoom(images_p* imageBank,config_p* config){ 
    char* roomConfigFile = (char*) (retrieveFromDict(config->dict, "roomConfigFile"))->data;
    if(roomConfigFile != NULL){
        room_p* room = w_malloc(sizeof(room_p));
        initRoom(room, imageBank, roomConfigFile);
        return room;
    }else{
        return NULL;
    }
}

void initRoom(room_p* room, images_p* imageBank, char* configFile){
    room->roomConf = NULL;
    room->roomConf = (config_p*) malloc(sizeof(config_p));
    initConfig(room->roomConf);
    buildConfigFromFile(room->roomConf, configFile, 0);
    room->imageBank = imageBank;
    room->imageId = saveImage(room->imageBank, getRoomSpriteFileName(room));
    initRoomTileCollections(room);
    fillRoomTiles(room);
}

void destructRoom(room_p* room){
    int i;
    deleteImage(room->imageBank, room->imageId);
    for(i = 0; i < LAYERS; i++){
        destructRoomTileCollection(room->roomTileCollection[i]);
        w_free(room->roomTileCollection[i]);
    }
    w_free(room->roomTileCollection);
}

stack* getRoomView(room_p* room, int layer, coordinates_p* center){
    int i,j;
    stack* s = NULL;
    viewParams_p vp = getViewParams(center, room, layer);
    for(i = vp.start_x; i < vp.end_x; i++){
        for(j = vp.start_y; j < vp.end_y; j++){
            view_p* view = w_malloc(sizeof(view_p));
            view->coordinates = getTileCollectionCoords(room->roomTileCollection[layer], i, j);
            if(view->coordinates != NULL){
                updateScreenLocation(view->coordinates, center);
                view->imageId = room->imageId;
                push_stack(&s, view);
            }else w_free(view);
        }
    }
    return s;
}

void updateScreenLocation(coordinates_p* coords, coordinates_p* center){
    int xDiff = coords->mapX - center->mapX;
    int yDiff = coords->mapY - center->mapY;
    coords->destX = center->destX + xDiff;
    coords->destY = center->destY + yDiff;
}

viewParams_p getViewParams(coordinates_p* center, room_p* room, int layer){
    viewParams_p vp;
    
    int upperX = getTileCollectionRows(room->roomTileCollection[layer])*TILESIZE;
    int upperY = getTileCollectionColumns(room->roomTileCollection[layer])*TILESIZE;
    
    vp.start_x = center->mapX - SCREEN_WIDTH;
    vp.end_x = center->mapX + SCREEN_WIDTH;
    vp.start_y = center->mapY - SCREEN_HEIGHT;
    vp.end_y = center->mapY + SCREEN_HEIGHT;
    
    vp.start_x = ((vp.start_x > 0) ? vp.start_x : 0) / TILESIZE;
    vp.end_x = ((vp.end_x < upperX) ? vp.end_x : upperX) / TILESIZE;
    vp.start_y = ((vp.start_y > 0) ? vp.start_y : 0) / TILESIZE;
    vp.end_y = ((vp.end_y < upperY) ? vp.end_y : upperY) / TILESIZE;
    return vp;
}

/* Initialization Functions
 * All of these should be replaced when config files are finalized. 
 */

char* getRoomSpriteFileName(room_p* room){
    return getStringFromDict(room->roomConf->dict, "sprite_sheet");
}

void initRoomTileCollections(room_p* room){
    int i;
    int roomH, roomW;
    room->roomTileCollection = w_malloc(LAYERS*sizeof(rtc_p*));
    for(i = 0; i < LAYERS; i++){
        room->roomTileCollection[i] = w_malloc(sizeof(rtc_p));
        roomW = getIntFromDict(room->roomConf->dict, "room_width");
        roomH = getIntFromDict(room->roomConf->dict, "room_height");
        initRoomTileCollection(room->roomTileCollection[i], roomW, roomH);
    }
}

void fillRoomTiles(room_p* room){

    LinkedList_p* tileList = getLinkedListFromDict(room->roomConf->dict, "tile_collection");
    LinkedListNode_p* current = getHeadLLNode(tileList);

    while(current != NULL){
        sdNode_p* tileDictNode = (sdNode_p*) current->data;
        StringDict_p* tileDict = (StringDict_p*) tileDictNode->data;

        coordinates_p* coords = w_malloc(sizeof(coordinates_p));
        coords->srcX = getIntFromDict(tileDict, "srcX");
        coords->srcY = getIntFromDict(tileDict, "srcY");
        coords->srcW = getIntFromDict(tileDict, "srcW");
        coords->srcH = getIntFromDict(tileDict, "srcH");
        coords->destW = getIntFromDict(tileDict, "destW");
        coords->destH = getIntFromDict(tileDict, "destH");
        coords->mapX = getIntFromDict(tileDict, "mapX");
        coords->mapY = getIntFromDict(tileDict, "mapY");
        coords->layer = getIntFromDict(tileDict, "layer");
        addTile(room->roomTileCollection[1], coords);

        current = current->next;
    }
}
