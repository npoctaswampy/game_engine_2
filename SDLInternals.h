#include <SDL2/SDL.h>

#ifndef SDLINTERNALS
#define SDLINTERNALS

typedef struct sdl_t {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *screen;
	SDL_Texture* texture;
} sdl_p;

void initializeSDL(sdl_p* sdlSystem);
void teardownSDL(sdl_p* sdlSystem);
void drawToScreen(coordinates_p* coordinates, sdl_p* sdlSystem, SDL_Surface* image);
void flipPage(sdl_p* sdlSystem);
SDL_Surface* getSurfaceFromFile(char* filename);
void freeSDLSurface(SDL_Surface* surface);
stack* getKeyStateCommand();

#endif