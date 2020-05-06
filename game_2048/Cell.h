//
// Created by fordring on 2020/5/2.
//

#ifndef CPPGAMES_CELL_H
#define CPPGAMES_CELL_H

#include "Piece.h"

class Cell{
private:
    Piece piece;
    bool null;
public:
    bool flag;
    Cell();
    Cell(bool null);
    bool merge(Piece p);
    bool canMerge(Piece p);
    bool isEmpty();
    bool isNull();
    bool insert(Piece piece);
    Piece getPiece();
    void clean();
};


#endif //CPPGAMES_CELL_H
