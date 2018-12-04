CFLAGS=-W -Wall -ggdb `sdl2-config --cflags`
LIBS=-lm `sdl2-config --libs` -lpthread
OBJS=game_main.o particle.o background.o resources.o
CC=gcc

BIN = game game_main.o Window.o Controller.o Player_game.o Room.o Background.o ImageBank.o SDLInternals.o stack.o MemManagement.o PlayerAnimation.o Frame.o RoomTileCollection.o Tile.o clean

all: $(BIN)

game: game_main.o stack.o SDLInternals.o MemManagement.o Window.o Controller.o Player_game.o Room.o Background.o ImageBank.o table.o PlayerAnimation.o Frame.o RoomTileCollection.o Tile.o
	$(CC) $(CFLAGS) game_main.o stack.o SDLInternals.o MemManagement.o Window.o Controller.o Player_game.o Room.o Background.o ImageBank.o table.o PlayerAnimation.o Frame.o RoomTileCollection.o Tile.o -o ./gameEx/game $(LIBS)
		
game_main.o: game_main.c SDLInternals.h MemManagement.h WindowDef/Window.h ControllerDef/Controller.h PlayerDef/Player.h ImageBankDef/ImageBank.h Common.h
	$(CC) $(CFLAGS) -c game_main.c $(LIBS)
	
Window.o: WindowDef/Window.c ControllerDef/Controller.h SDLInternals.h ImageBankDef/ImageBank.h Common.h
	$(CC) $(CFLAGS) -c WindowDef/Window.c $(LIBS)
	
Controller.o: ControllerDef/Controller.h MemManagement.h Common.h PlayerDef/Player.h RoomDef/Room.h BackgroundDef/Background.h
	$(CC) $(CFLAGS) -c ControllerDef/Controller.c $(LIBS)

Player_game.o: PlayerDef/Player.h Common.h ImageBankDef/ImageBank.h PlayerDef/PlayerAnimation.h PlayerDef/Frame.h
	$(CC) $(CFLAGS) -c PlayerDef/Player.c -o Player_game.o $(LIBS)
	
Room.o: RoomDef/Room.c RoomDef/Room.h ImageBankDef/ImageBank.h Common.h RoomDef/RoomTileCollection.h RoomDef/Tile.h
	$(CC) $(CFLAGS) -c RoomDef/Room.c -o Room.o $(LIBS)
	
Background.o: BackgroundDef/Background.h Common.h ImageBankDef/ImageBank.h
	$(CC) $(CFLAGS) -c BackgroundDef/Background.c -o Background.o $(LIBS)
	
ImageBank.o: ImageBankDef/ImageBank.c ImageBankDef/ImageBank.h SDLInternals.h Common.h
	$(CC) $(CFLAGS) -c ImageBankDef/ImageBank.c $(LIBS)

SDLInternals.o: SDLInternals.c SDLInternals.h MemManagement.h Common.h
	$(CC) $(CFLAGS) -c SDLInternals.c $(LIBS)
	
PlayerAnimation.o: PlayerDef/PlayerAnimation.c PlayerDef/PlayerAnimation.h PlayerDef/Frame.h Common.h
	$(CC) $(CFLAGS) -c PlayerDef/PlayerAnimation.c
	
RoomTileCollection.o: RoomDef/RoomTileCollection.c RoomDef/RoomTileCollection.h RoomDef/Tile.h Common.h
	$(CC) $(CFLAGS) -c RoomDef/RoomTileCollection.c
	
Frame.o: PlayerDef/Frame.c PlayerDef/Frame.h
	$(CC) $(CFLAGS) -c PlayerDef/Frame.c

Tile.o: RoomDef/Tile.c RoomDef/Tile.h Common.h
	$(CC) $(CFLAGS) -c RoomDef/Tile.c
	
stack.o: DataStructures/stack.c DataStructures/stack.h MemManagement.h
	$(CC) $(CFLAGS) -c DataStructures/stack.c
	
table.o: DataStructures/table.c DataStructures/table.h MemManagement.h
	$(CC) $(CFLAGS) -c DataStructures/table.c
	
MemManagement.o: MemManagement.c MemManagement.h
	$(CC) $(CFLAGS) -c MemManagement.c

clean:
	rm -f *.o  

