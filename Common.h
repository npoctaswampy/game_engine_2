#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef MEMMANAGE
#define MEMMANAGE
#include "MemManagement.h"
#endif

#ifndef STACK
#define STACK
#include "stack.h"
#endif

#ifndef TABLE
#define TABLE
#include "table.h"
#endif

#ifndef COMMON
#define COMMON

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

typedef struct coordinates_t{
	int srcX;
	int srcY; 
	int srcW; 
	int srcH; 
	int destX;
	int destY;
	int destW;
	int destH;
        int mapX;
        int mapY;
        int layer;
} coordinates_p;

typedef struct view_t{
    int imageId;
    coordinates_p* coordinates;
} view_p;

typedef enum{FIRST,Q,ESCAPE,F,P,
	     LEFT,RIGHT,UP,DOWN,
	     X,Z,E,NONE
	     } key;
             
#define LAYERS 10
#endif
