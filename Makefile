CFLAGS=-W -Wall -ggdb `sdl2-config --cflags`
LIBS=-lm `sdl2-config --libs` -lpthread
OBJS=game_main.o particle.o background.o resources.o
CC=gcc

BIN = game iotest imagetabletest game_main.o ioTester.o imageTableTester.o Window.o Controller.o Player_game.o Room.o Background.o ImageBank.o SDLInternals.o stack.o MemManagement.o PlayerAnimation.o Frame.o RoomTileCollection.o Tile.o clean

all: $(BIN)

game: game_main.o stack.o SDLInternals.o MemManagement.o Window.o Controller.o Player_game.o Room.o Background.o ImageBank.o table.o PlayerAnimation.o Frame.o RoomTileCollection.o Tile.o
	$(CC) $(CFLAGS) game_main.o stack.o SDLInternals.o MemManagement.o Window.o Controller.o Player_game.o Room.o Background.o ImageBank.o table.o PlayerAnimation.o Frame.o RoomTileCollection.o Tile.o -o ./gameEx/game $(LIBS)
		
iotest: ioTester.o stack.o SDLInternals.o MemManagement.o
	$(CC) $(CFLAGS) ioTester.o stack.o SDLInternals.o MemManagement.o -o ./testEx/iotest $(LIBS)
	
imagetabletest: imageTableTester.o table.o SDLInternals.o MemManagement.o ImageBank.o stack.o table.o
	$(CC) $(CFLAGS) imageTableTester.o table.o stack.o SDLInternals.o MemManagement.o ImageBank.o -o ./testEx/imagetabletest $(LIBS)

game_main.o: game_main.c stack.h SDLInternals.h MemManagement.h Window.h Controller.h PlayerDef/Player.h ImageBank.h table.h Common.h
	$(CC) $(CFLAGS) -c game_main.c $(LIBS)
	
ioTester.o: ioTester.c stack.h Common.h SDLInternals.h MemManagement.h
	$(CC) $(CFLAGS) -c ioTester.c $(LIBS)
	
imageTableTester.o: imageTableTester.c ImageBank.h SDLInternals.h MemManagement.h table.h Common.h stack.h
	$(CC) $(CFLAGS) -c imageTableTester.c $(LIBS)
	
Window.o: Window.c Controller.h SDLInternals.h ImageBank.h Common.h
	$(CC) $(CFLAGS) -c Window.c $(LIBS)
	
Controller.o: Controller.h MemManagement.h Common.h PlayerDef/Player.h RoomDef/Room.h Background.h
	$(CC) $(CFLAGS) -c Controller.c $(LIBS)

Player_game.o: PlayerDef/Player.h Common.h ImageBank.h PlayerDef/PlayerAnimation.h PlayerDef/Frame.h
	$(CC) $(CFLAGS) -c PlayerDef/Player.c -o Player_game.o $(LIBS)
	
Room.o: RoomDef/Room.c RoomDef/Room.h ImageBank.h Common.h RoomDef/RoomTileCollection.h RoomDef/Tile.h
	$(CC) $(CFLAGS) -c RoomDef/Room.c -o Room.o $(LIBS)
	
Background.o: Background.h Common.h ImageBank.h
	$(CC) $(CFLAGS) -c Background.c -o Background.o $(LIBS)
	
ImageBank.o: ImageBank.c ImageBank.h SDLInternals.h table.h Common.h stack.h
	$(CC) $(CFLAGS) -c ImageBank.c $(LIBS)

SDLInternals.o: SDLInternals.c SDLInternals.h stack.h MemManagement.h Common.h
	$(CC) $(CFLAGS) -c SDLInternals.c $(LIBS)
	
PlayerAnimation.o: PlayerDef/PlayerAnimation.c PlayerDef/PlayerAnimation.h PlayerDef/Frame.h Common.h
	$(CC) $(CFLAGS) -c PlayerDef/PlayerAnimation.c
	
RoomTileCollection.o: RoomDef/RoomTileCollection.c RoomDef/RoomTileCollection.h RoomDef/Tile.h Common.h
	$(CC) $(CFLAGS) -c RoomDef/RoomTileCollection.c
	
Frame.o: PlayerDef/Frame.c PlayerDef/Frame.h
	$(CC) $(CFLAGS) -c PlayerDef/Frame.c

Tile.o: RoomDef/Tile.c RoomDef/Tile.h Common.h
	$(CC) $(CFLAGS) -c RoomDef/Tile.c
	
stack.o: stack.c stack.h MemManagement.h
	$(CC) $(CFLAGS) -c stack.c
	
table.o: table.c table.h MemManagement.h
	$(CC) $(CFLAGS) -c table.c
	
MemManagement.o: MemManagement.c MemManagement.h
	$(CC) $(CFLAGS) -c MemManagement.c

clean:
	rm -f *.o  

