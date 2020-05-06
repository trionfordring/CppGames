//
// Created by fordring on 2020/5/2.
//

#include "Game2048.h"
#include <random>
#include <time.h>

Game2048::Game2048(float rand4Rate,int width,int heigh):rand4Rate(rand4Rate*RAND_4_RATE_ACCURACY),chessboard(width,heigh){}

void Game2048::init(int initPieceNum) {
    srand(clock());
}

Piece Game2048::randomPiece() {
    return (rand()%RAND_4_RATE_ACCURACY)>rand4Rate?Piece(2):Piece(4);
}

Point Game2048::randomEmptyPoint() {
    Point point = randomPoint();

}

Point Game2048::randomPoint() {
    int width=chessboard.getWidth(),height=chessboard.getHeight();
    return {rand()%width,rand()%height};
}

