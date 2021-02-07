CFLAGS=-W -Wall -ggdb `sdl2-config --cflags`
LIBS=-lm `sdl2-config --libs` -lpthread
OBJS=game_main.o particle.o background.o resources.o
CC=gcc

BIN = designer designer_main.o clean

all: $(BIN)

designer: designer_main.o
	$(CC) $(CFLAGS) designer_main.o -o ./designerEx/designer $(LIBS)
		
designer_main.o: designer_main.c
	$(CC) $(CFLAGS) -c designer_main.c $(LIBS)