//
// Created by fordring on 2020/5/2.
//

#include "Cell.h"
#include "Piece.h"

Cell::Cell() : flag(false),null(false) {}
Cell::Cell(bool null): flag(false),null(null)  {}
bool Cell::merge(Piece p){
    if (canMerge(p)){
        piece.num += p.num;
        return true;
    }
    return false;
}

bool Cell::canMerge(Piece p){
    if(isNull()||flag){
        return false;
    }
    return piece.num == p.num;
}


bool Cell::isEmpty(){
    return !piece.hasNum();
}

bool Cell::insert(Piece piece) {
    bool ans = true;
    if(isNull()||!isEmpty()){
        ans = false;
    }
    this->piece = piece;
    return true;
}

Piece Cell::getPiece(){
    return piece;
}

void Cell::clean(){
    flag = false;
    piece.clean();
}

bool Cell::isNull(){
    return null;
}
