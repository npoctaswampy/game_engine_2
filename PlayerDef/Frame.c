#include <stdio.h>
#include <stdlib.h>
#include "Frame.h"

void initFrame(frame_p* frame, int column, int row){
    frame->column = column;
    frame->row = row;
}