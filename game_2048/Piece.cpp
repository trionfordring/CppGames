//
// Created by fordring on 2020/5/2.
//

#include "Piece.h"

Piece::Piece():num(0){

}
Piece::Piece(int num):num(num) {}
bool Piece::hasNum(){
    return num!=0;
}
bool Piece::clean(){
    num=0;
}