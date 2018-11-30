#include <stdio.h>
#include <stdlib.h>
#include "Common.h"
#include "SDLInternals.h"


int main()
{
    sdl_p* sdlSystem = w_malloc(sizeof(sdlSystem));
    initializeSDL(sdlSystem);
    
    int quit = 0;
    key* k = NULL;
    while(quit==0){
        stack* s = getKeyStateCommand();
        while((k=pop_stack(&s)) != NULL){
            if(*k != FIRST) printf("%d\n",*k);
            if(*k == Q || *k == ESCAPE) quit = 1;
            w_free(k);
        }
        freeStack(s);
    }
    
    teardownSDL(sdlSystem);
    return 0;
}
