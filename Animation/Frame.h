
#ifndef FRAME
#define FRAME

typedef struct frame_t{
    int column;
    int row;
}frame_p;

void initFrame(frame_p* frame, int column, int row);

#endif