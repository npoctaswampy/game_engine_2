#include <stdio.h>
#include <stdlib.h>
#include "MemManagement.h"
int count = 0;

void * w_malloc(size_t size){
    count++;
    //printf("%d items allocated\n",count);
    return malloc(size);
}

void w_free(void *ptr){
    if(ptr != NULL){
        count--;
        //printf("%d items allocated %p\n",count,ptr);
        free(ptr);
    }
}
