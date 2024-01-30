cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(untitled main.cpp
        Board.h
        Menu.cpp
        Menu.h
        Game.cpp
        Game.h
        Game.cpp
        Bot.cpp
        Bot.h
        Board.cpp
        Board.h)
