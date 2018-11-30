#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "SDLInternals.h"

void initializeSDL(sdl_p* sdlSystem){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
    	}

	sdlSystem->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
                                        0x00FF0000,
                                        0x0000FF00,
                                        0x000000FF,
                                        0xFF000000);

	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &(sdlSystem->window), &(sdlSystem->renderer));

	sdlSystem->texture = SDL_CreateTexture(sdlSystem->renderer,SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                           SCREEN_WIDTH, SCREEN_HEIGHT);

	if (sdlSystem->window == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
	}

}

void teardownSDL(sdl_p* sdlSystem){
	/* Free the memory that was allocated to the bitmaps. */
	SDL_FreeSurface(sdlSystem->screen);
	SDL_DestroyTexture(sdlSystem->texture);
	SDL_DestroyRenderer(sdlSystem->renderer);
	SDL_DestroyWindow(sdlSystem->window);
        SDL_VideoQuit();
	SDL_Quit();
}

void drawToScreen(coordinates_p* coordinates, sdl_p* sdlSystem, SDL_Surface* image){
	SDL_Rect src, dest;

	Uint32 colorkey = SDL_MapRGB(image->format, 0, 0, 255);

	SDL_SetColorKey(image, SDL_TRUE, colorkey);

	src.x = coordinates->srcX;
	src.y = coordinates->srcY;
	src.w = coordinates->srcW;
	src.h = coordinates->srcH;
	dest.x = coordinates->destX;
	dest.y = coordinates->destY;
	dest.w = coordinates->destW;
	dest.h = coordinates->destH;

	SDL_BlitSurface(image, &src, sdlSystem->screen, &dest);
}

void flipPage(sdl_p* sdlSystem){
	SDL_UpdateTexture(sdlSystem->texture, NULL, sdlSystem->screen->pixels, sdlSystem->screen->pitch);
	SDL_RenderCopy(sdlSystem->renderer, sdlSystem->texture, NULL, NULL);
	SDL_RenderPresent(sdlSystem->renderer);
}

SDL_Surface* getSurfaceFromFile(char* filename){
    SDL_Surface* sf = SDL_LoadBMP(filename);
    if(sf == NULL){
        printf("Unable to load bitmap %s\n",filename);
    }
    return sf;
}

void freeSDLSurface(SDL_Surface* surface){
    SDL_FreeSurface(surface);
}

void pushKeyToStack(stack** s, key keyVal){
	key* node = (key*) w_malloc(sizeof(key));
	*node = keyVal;
	push_stack(s, node);
}

stack* getKeyStateCommand(){
	stack* ret_stack = NULL;

	SDL_PumpEvents();
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_Q]) 
		pushKeyToStack(&ret_stack,Q);
	if (keystate[SDL_SCANCODE_ESCAPE]) 
		pushKeyToStack(&ret_stack,ESCAPE);
	if (keystate[SDL_SCANCODE_F]) 
		pushKeyToStack(&ret_stack,F);
	if (keystate[SDL_SCANCODE_P]) 
		pushKeyToStack(&ret_stack,P);
	if (keystate[SDL_SCANCODE_LEFT]) 
		pushKeyToStack(&ret_stack,LEFT);
	if (keystate[SDL_SCANCODE_RIGHT]) 
		pushKeyToStack(&ret_stack,RIGHT);
	if (keystate[SDL_SCANCODE_UP]) 
		pushKeyToStack(&ret_stack,UP);
	if (keystate[SDL_SCANCODE_DOWN]) 
		pushKeyToStack(&ret_stack,DOWN);
	if (keystate[SDL_SCANCODE_X]) 
		pushKeyToStack(&ret_stack,X);
	if (keystate[SDL_SCANCODE_Z]) 
		pushKeyToStack(&ret_stack,Z);
	if (keystate[SDL_SCANCODE_E]) 
		pushKeyToStack(&ret_stack,E);

	return ret_stack;
}

