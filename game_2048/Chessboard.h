//
// Created by fordring on 2020/5/2.
//

#ifndef CPPGAMES_CHESSBOARD_H
#define CPPGAMES_CHESSBOARD_H

#include <vector>

#include "Cell.h"
#include "Forward.h"

using namespace std;

class Chessboard{
private:
    vector<vector<Cell>> board;
    int maxNum;
    bool merge(const Forward& forward);
    bool land(const Forward& forward);
    bool canSlide(Point point,const Forward& forward);
public:
    Chessboard(int width=4,int height=4);
    bool insertPiece(int x,int y,Piece piece);
    bool canSlide(const Forward& forward);
    bool slide(const Forward& forward);
    bool isEmpty(Point point);
    int getWidth();
    int getHeight();
    int getPieceCount();
    Cell& getCell(Point point);
    Cell popCell(Point point);
    bool insert(Point point,Piece piece);

};


#endif //CPPGAMES_CHESSBOARD_H
