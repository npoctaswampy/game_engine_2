cmake_minimum_required(VERSION 3.14)
project(game_engine_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(BackgroundDef)
include_directories(ConfigDef)
include_directories(ControllerDef)
include_directories(DataStructures)
include_directories(ImageBankDef)
include_directories(PlayerDef)
include_directories(RoomDef)
include_directories(WindowDef)

add_executable(game_engine_2
        BackgroundDef/Background.c
        BackgroundDef/Background.h
        ConfigDef/Config.c
        ConfigDef/Config.h
        ControllerDef/Controller.c
        ControllerDef/Controller.h
        DataStructures/LinkedList.c
        DataStructures/LinkedList.h
        DataStructures/stack.c
        DataStructures/stack.h
        DataStructures/StringDict.c
        DataStructures/StringDict.h
        DataStructures/table.c
        DataStructures/table.h
        gameEx/config/rooms/test_room1.txt
        gameEx/config/master.txt
        gameEx/config/sampleText.txt
        gameEx/game
        ImageBankDef/ImageBank.c
        ImageBankDef/ImageBank.h
        PlayerDef/Frame.c
        PlayerDef/Frame.h
        PlayerDef/Player.c
        PlayerDef/Player.h
        PlayerDef/PlayerAnimation.c
        PlayerDef/PlayerAnimation.h
        PlayerDef/PlayerMaker.c
        RoomDef/Room.c
        RoomDef/Room.h
        RoomDef/RoomTileCollection.c
        RoomDef/RoomTileCollection.h
        RoomDef/Tile.c
        RoomDef/Tile.h
        WindowDef/Window.c
        WindowDef/Window.h
        Common.h
        game_main.c
        Makefile
        MemManagement.c
        MemManagement.h
        SDLInternals.c
        SDLInternals.h)
