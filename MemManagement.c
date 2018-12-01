#include <stdio.h>
#include <stdlib.h>
#include "MemManagement.h"
int count = 0;

void * w_malloc(size_t size){
#ifdef DEBUG
    count++;
    printf("%d items allocated\n",count);
#endif
    return malloc(size);
}

void w_free(void *ptr){
    if(ptr != NULL){
#ifdef DEBUG
        count--;
        printf("%d items allocated %p\n",count,ptr);
#endif
        free(ptr);
    }
}
