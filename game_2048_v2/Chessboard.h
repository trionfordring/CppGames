//
// Created by fordring on 2020/5/3.
//

#ifndef CPPGAMES_CHESSBOARD_H
#define CPPGAMES_CHESSBOARD_H

#include <vector>
#include "Cell.h"
#include "Point.h"

class Chessboard {
private:
    std::vector<std::vector<Cell>> board;
    int maxNum;
    bool merge_UP();
    bool merge_DOWN();
    bool merge_RIGHT();
    bool merge_LEFT();
    bool land_UP();
    bool land_DOWN();
    bool land_LEFT();
    bool land_RIGHT();
public:
    Chessboard(int width=4,int height=4);
    bool insertPiece(Point point,int num);
    bool canSlide();
    bool canSlide_UP();
    bool canSlide_DOWN();
    bool canSlide_LEFT();
    bool canSlide_RIGHT();
    bool slide_UP();
    bool slide_DOWN();
    bool slide_RIGHT();
    bool slide_LEFT();
    bool isEmpty(Point point);
    int getWidth();
    int getHeight();
    int getPieceCount();
    int getPiece(Point point);
    int setPiece(Point point,int num);
    int getMaxPiece();
};


#endif //CPPGAMES_CHESSBOARD_H
