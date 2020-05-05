cmake_minimum_required(VERSION 3.15)
project(CppGames)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(CppGames main.cpp game_2048_v2/Game2048.cpp game_2048_v2/Game2048.h game_2048_v2/Chessboard.cpp game_2048_v2/Chessboard.h game_2048_v2/Cell.cpp game_2048_v2/Cell.h game_2048_v2/Point.h)