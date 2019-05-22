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
    sdNode_p* node = retrieveFromDict(room->roomConf->dict, "sprite_sheet");
    return (char*) node->data;
}

void initRoomTileCollections(room_p* room){
    int i;
    int roomH, roomW;
    room->roomTileCollection = w_malloc(LAYERS*sizeof(rtc_p*));
    for(i = 0; i < LAYERS; i++){
        room->roomTileCollection[i] = w_malloc(sizeof(rtc_p));
        roomW = *((int*) (retrieveFromDict(room->roomConf->dict, "room_width"))->data);
        roomH = *((int*) (retrieveFromDict(room->roomConf->dict, "room_height"))->data);
        initRoomTileCollection(room->roomTileCollection[i], roomW, roomH);
    }
}

void fillRoomTiles(room_p* room){
    int i,j;
    int upperX = getTileCollectionRows(room->roomTileCollection[1]);
    int upperY = getTileCollectionColumns(room->roomTileCollection[1]);

    sdNode_p* node = retrieveFromDict(room->roomConf->dict, "tile_collection");
    LinkedList_p* tileList = (LinkedList_p*) node->data;

    LinkedListNode_p* head = getHeadLLNode(tileList);
    sdNode_p* tileDictNode = (sdNode_p*) head->data;
    StringDict_p* tileDict = (StringDict_p*) tileDictNode->data;

    for(i=0; i < upperX; i++){
        for(j=0; j<upperY; j++){
            coordinates_p* coords = w_malloc(sizeof(coordinates_p));
            coords->srcX = *((int*) (retrieveFromDict(tileDict, "srcX"))->data);
            coords->srcY = *((int*) (retrieveFromDict(tileDict, "srcY"))->data);
            coords->srcW = *((int*) (retrieveFromDict(tileDict, "srcW"))->data);
            coords->srcH = *((int*) (retrieveFromDict(tileDict, "srcH"))->data);
            coords->destW = *((int*) (retrieveFromDict(tileDict, "destW"))->data);
            coords->destH = *((int*) (retrieveFromDict(tileDict, "destH"))->data);
            coords->mapX = *((int*) (retrieveFromDict(tileDict, "mapX"))->data);
            coords->mapY = *((int*) (retrieveFromDict(tileDict, "mapY"))->data);
            coords->layer = *((int*) (retrieveFromDict(tileDict, "layer"))->data);
            addTile(room->roomTileCollection[1], coords);
        }
    }
}
