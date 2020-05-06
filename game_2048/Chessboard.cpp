//
// Created by fordring on 2020/5/2.
//

#include "Chessboard.h"

Cell NULL_CELL(true);

bool Chessboard::merge(const Forward& forward){
    bool ans = false;
    auto callback = [this,&ans](Point point,const Forward& forward) -> void {
        Cell& currentCell = getCell(point);
        Point nextPoint = offset(point,forward);
        Cell& nextCell = getCell(nextPoint);
        while(!nextCell.isNull()&&nextCell.isEmpty()){
            nextPoint = offset(nextPoint,forward);
            nextCell = getCell(nextPoint);
        }
        if(nextCell.canMerge(currentCell.getPiece())){
            nextCell.merge(currentCell.getPiece());
            nextCell.flag= true;
            currentCell.clean();
            ans= true;
        }
    };
    forward.foreach({0,getHeight()-1}, {getWidth()-1,0}, callback);
    return ans;
}
bool Chessboard::land(const Forward& forward){
    bool ans = false;
    forward.foreach({0,getHeight()-1}, {getWidth()-1,0}, [this,&ans](Point point,const Forward& forward) -> void {
        Cell& currentCell = getCell(point);
        Point nextPoint = offset(point,forward);
        Cell& nextCell = getCell(nextPoint);
        while(!nextCell.isNull()&&nextCell.isEmpty()){
            nextPoint = offset(nextPoint,forward);
            nextCell = getCell(nextPoint);
        }
        if(nextCell.canMerge(currentCell.getPiece())){
            ans= true;
        }
    });
    return ans;
}

Chessboard::Chessboard(int width, int height) : board(height, vector<Cell>(width)), maxNum(0) {
}

bool Chessboard::insertPiece(int x, int y, Piece piece){
    return board[y][x].merge(piece);
}

bool Chessboard::canSlide(Point point, const Forward &forward) {

}

bool Chessboard::canSlide(const Forward& forward){

}

bool Chessboard::slide(const Forward& forward){
    return merge(forward) && land(forward);
}

int Chessboard::getHeight() {
    return board.size();
}

int Chessboard::getWidth() {
    return board[0].size();
}

Cell& Chessboard::getCell(Point point) {
    if(point.x<getWidth()&&point.x>=0&&point.y<getHeight()&&point.y>=0){
        return board[point.y][point.x];
    }
    NULL_CELL=Cell(true);
    return NULL_CELL;
}

bool Chessboard::isEmpty(Point point) {
    Cell cell = getCell(point);
    if(cell.isNull()){
        return false;
    }
    return cell.isEmpty();
}

int Chessboard::getPieceCount() {
    int cnt=0;
    for(int y=0;y<board.size();y++)
        for(int x=0;x<board[0].size();x++){
            if(!getCell({x,y}).isEmpty()){
                cnt++;
            }
        }
    return cnt;
}

Cell Chessboard::popCell(Point point) {
    Cell cell = getCell(point);
    if(!cell.isNull()){
        board[point.y][point.x].clean();
    }
    return cell;
}

bool Chessboard::insert(Point point, Piece piece) {
    return getCell(point).insert(piece);
}