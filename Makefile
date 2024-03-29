CFLAGS=-W -Wall -ggdb `sdl2-config --cflags`
LIBS=-lm `sdl2-config --libs` -lpthread
OBJS=game_main.o particle.o background.o resources.o
CC=gcc

BIN = game game_main.o Window.o Controller.o Config.o Player_game.o Room.o Background.o ImageBank.o SDLInternals.o stack.o MemManagement.o Animation.o Frame.o RoomTileCollection.o Tile.o MailSystem.o Mailbox.o StringDict.o LinkedList.o clean

all: $(BIN)

game: game_main.o stack.o SDLInternals.o MemManagement.o Window.o Controller.o Config.o Player_game.o Room.o Background.o ImageBank.o table.o Animation.o Frame.o RoomTileCollection.o Tile.o StringDict.o LinkedList.o MailSystem.o Mailbox.o
	$(CC) $(CFLAGS) game_main.o stack.o SDLInternals.o MemManagement.o Window.o Controller.o Config.o Player_game.o Room.o Background.o ImageBank.o table.o Animation.o Frame.o RoomTileCollection.o Tile.o MailSystem.o Mailbox.o StringDict.o LinkedList.o -o ./gameEx/game $(LIBS)
		
game_main.o: game_main.c SDLInternals.h MemManagement.h WindowDef/Window.h ControllerDef/Controller.h PlayerDef/Player.h ImageBankDef/ImageBank.h MailSystemDef/MailSystem.h Common.h
	$(CC) $(CFLAGS) -c game_main.c $(LIBS)
	
Window.o: WindowDef/Window.c ControllerDef/Controller.h SDLInternals.h ImageBankDef/ImageBank.h MailSystemDef/MailSystem.h Common.h
	$(CC) $(CFLAGS) -c WindowDef/Window.c $(LIBS)
	
Controller.o: ControllerDef/Controller.h MemManagement.h Common.h PlayerDef/Player.h RoomDef/Room.h BackgroundDef/Background.h 
	$(CC) $(CFLAGS) -c ControllerDef/Controller.c $(LIBS)
	
Config.o: ConfigDef/Config.h DataStructures/StringDict.h DataStructures/table.h DataStructures/LinkedList.h
	$(CC) $(CFLAGS) -c ConfigDef/Config.c -o Config.o $(LIBS)
	
Player_game.o: PlayerDef/Player.h Common.h ImageBankDef/ImageBank.h Animation/Animation.h Animation/Frame.h
	$(CC) $(CFLAGS) -c PlayerDef/Player.c -o Player_game.o $(LIBS)
	
Room.o: RoomDef/Room.c RoomDef/Room.h ImageBankDef/ImageBank.h Common.h RoomDef/RoomTileCollection.h RoomDef/Tile.h
	$(CC) $(CFLAGS) -c RoomDef/Room.c -o Room.o $(LIBS)
	
Background.o: BackgroundDef/Background.h Common.h ImageBankDef/ImageBank.h
	$(CC) $(CFLAGS) -c BackgroundDef/Background.c -o Background.o $(LIBS)
	
ImageBank.o: ImageBankDef/ImageBank.c ImageBankDef/ImageBank.h SDLInternals.h Common.h
	$(CC) $(CFLAGS) -c ImageBankDef/ImageBank.c $(LIBS)

SDLInternals.o: SDLInternals.c SDLInternals.h MemManagement.h Common.h
	$(CC) $(CFLAGS) -c SDLInternals.c $(LIBS)
	
Animation.o: Animation/Animation.c Animation/Animation.h Animation/Frame.h Common.h
	$(CC) $(CFLAGS) -c Animation/Animation.c
	
RoomTileCollection.o: RoomDef/RoomTileCollection.c RoomDef/RoomTileCollection.h RoomDef/Tile.h Common.h
	$(CC) $(CFLAGS) -c RoomDef/RoomTileCollection.c
	
Frame.o: Animation/Frame.c Animation/Frame.h
	$(CC) $(CFLAGS) -c Animation/Frame.c

Tile.o: RoomDef/Tile.c RoomDef/Tile.h Common.h
	$(CC) $(CFLAGS) -c RoomDef/Tile.c
		
MailSystem.o: MailSystemDef/MailSystem.c MailSystemDef/MailSystem.h  MailSystemDef/MailboxDef/Mailbox.h Common.h
	$(CC) $(CFLAGS) -c MailSystemDef/MailSystem.c 
	
Mailbox.o: MailSystemDef/MailboxDef/Mailbox.c MailSystemDef/MailboxDef/Mailbox.h Common.h
	$(CC) $(CFLAGS) -c MailSystemDef/MailboxDef/Mailbox.c

StringDict.o: DataStructures/StringDict.c DataStructures/StringDict.h Common.h
	$(CC) $(CFLAGS) -c DataStructures/StringDict.c
	
LinkedList.o: DataStructures/LinkedList.c DataStructures/LinkedList.h Common.h
	$(CC) $(CFLAGS) -c DataStructures/LinkedList.c
	
stack.o: DataStructures/stack.c DataStructures/stack.h MemManagement.h
	$(CC) $(CFLAGS) -c DataStructures/stack.c
	
table.o: DataStructures/table.c DataStructures/table.h MemManagement.h
	$(CC) $(CFLAGS) -c DataStructures/table.c
	
MemManagement.o: MemManagement.c MemManagement.h
	$(CC) $(CFLAGS) -c MemManagement.c

clean:
	rm -f *.o  

