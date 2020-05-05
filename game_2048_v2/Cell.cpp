//
// Created by fordring on 2020/5/3.
//

#include "Cell.h"

bool Cell::isEmpty() {
    return num==0;
}

Cell::Cell():flag(false),num(0) {}