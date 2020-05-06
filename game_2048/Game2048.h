//
// Created by fordring on 2020/5/2.
//

#ifndef CPPGAMES_GAME2048_H
#define CPPGAMES_GAME2048_H

#include "Chessboard.h"

const int RAND_4_RATE_ACCURACY=100000;
class Game2048 {
private:
    int rand4Rate;
    Chessboard chessboard;
    Piece randomPiece();
    Point randomPoint();
    Point randomEmptyPoint();
public:
    Game2048(float rand4Rate=0.25,int width=4,int heigh=4);
    void init(int initPieceNum=2);

};


#endif //CPPGAMES_GAME2048_H
