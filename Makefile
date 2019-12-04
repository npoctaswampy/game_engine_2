INCLUDE_PATH= -IC:\Users\npoct\Documents\dev\c\dev-libs\SDL2\include -IC:\Users\npoct\Documents\dev\c\dev-libs\TTF\include
LIBRARY_PATH= -LC:\Users\npoct\Documents\dev\c\dev-libs\SDL2\lib -LC:\Users\npoct\Documents\dev\c\dev-libs\TTF\lib
COMPILER_FLAGS = -w -g -Wl,-subsystem,windows
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lm
OBJS=game_main.o particle.o background.o resources.o
CC=gcc

BIN = game game_main.o Window.o Controller.o Config.o Player_game.o Room.o Background.o ImageBank.o SDLInternals.o stack.o MemManagement.o Animation.o Frame.o RoomTileCollection.o Tile.o StringDict.o LinkedList.o clean

all: $(BIN)

game: game_main.o stack.o SDLInternals.o MemManagement.o Window.o Controller.o Config.o Player_game.o Room.o Background.o ImageBank.o table.o Animation.o Frame.o RoomTileCollection.o Tile.o StringDict.o LinkedList.o
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) game_main.o stack.o SDLInternals.o MemManagement.o Window.o Controller.o Config.o Player_game.o Room.o Background.o ImageBank.o table.o Animation.o Frame.o RoomTileCollection.o Tile.o StringDict.o LinkedList.o -o ./gameEx/game.exe $(LINKER_FLAGS)
		
game_main.o: game_main.c SDLInternals.h MemManagement.h WindowDef/Window.h ControllerDef/Controller.h PlayerDef/Player.h ImageBankDef/ImageBank.h Common.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c game_main.c $(LINKER_FLAGS)
	
Window.o: WindowDef/Window.c ControllerDef/Controller.h SDLInternals.h ImageBankDef/ImageBank.h Common.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c WindowDef/Window.c $(LINKER_FLAGS)
	
Controller.o: ControllerDef/Controller.h MemManagement.h Common.h PlayerDef/Player.h RoomDef/Room.h BackgroundDef/Background.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c ControllerDef/Controller.c $(LINKER_FLAGS)
	
Config.o: ConfigDef/Config.h DataStructures/StringDict.h DataStructures/table.h DataStructures/LinkedList.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c ConfigDef/Config.c -o Config.o $(LINKER_FLAGS)
	
Player_game.o: PlayerDef/Player.h Common.h ImageBankDef/ImageBank.h Animation/Animation.h Animation/Frame.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c PlayerDef/Player.c -o Player_game.o $(LINKER_FLAGS)
	
Room.o: RoomDef/Room.c RoomDef/Room.h ImageBankDef/ImageBank.h Common.h RoomDef/RoomTileCollection.h RoomDef/Tile.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c RoomDef/Room.c -o Room.o $(LINKER_FLAGS)
	
Background.o: BackgroundDef/Background.h Common.h ImageBankDef/ImageBank.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c BackgroundDef/Background.c -o Background.o $(LINKER_FLAGS)
	
ImageBank.o: ImageBankDef/ImageBank.c ImageBankDef/ImageBank.h SDLInternals.h Common.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c ImageBankDef/ImageBank.c $(LINKER_FLAGS)

SDLInternals.o: SDLInternals.c SDLInternals.h MemManagement.h Common.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c SDLInternals.c $(LINKER_FLAGS)
	
Animation.o: Animation/Animation.c Animation/Animation.h Animation/Frame.h Common.h
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -c Animation/Animation.c
	
RoomTileCollection.o: RoomDef/RoomTileCollection.c RoomDef/RoomTileCollection.h RoomDef/Tile.h Common.h
	$(CC) $(COMPILER_FLAGS) -c RoomDef/RoomTileCollection.c
	
Frame.o: Animation/Frame.c Animation/Frame.h
	$(CC) $(COMPILER_FLAGS) -c Animation/Frame.c

Tile.o: RoomDef/Tile.c RoomDef/Tile.h Common.h
	$(CC) $(COMPILER_FLAGS) -c RoomDef/Tile.c

StringDict.o: DataStructures/StringDict.c DataStructures/StringDict.h Common.h
	$(CC) $(COMPILER_FLAGS) -c DataStructures/StringDict.c
	
LinkedList.o: DataStructures/LinkedList.c DataStructures/LinkedList.h Common.h
	$(CC) $(COMPILER_FLAGS) -c DataStructures/LinkedList.c
	
stack.o: DataStructures/stack.c DataStructures/stack.h MemManagement.h
	$(CC) $(COMPILER_FLAGS) -c DataStructures/stack.c
	
table.o: DataStructures/table.c DataStructures/table.h MemManagement.h
	$(CC) $(COMPILER_FLAGS) -c DataStructures/table.c
	
MemManagement.o: MemManagement.c MemManagement.h
	$(CC) $(COMPILER_FLAGS) -c MemManagement.c
	
clean:
	del *.o


