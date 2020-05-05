//
// Created by fordring on 2020/5/3.
//

#include "Chessboard.h"

using std::vector;

Chessboard::Chessboard(int width, int height) : board(height, vector<Cell>(width)), maxNum(0) {
}

bool Chessboard::insertPiece(Point point, int num) {
    if(isEmpty(point)){
        setPiece(point,num);
        return true;
    }
    return false;
}

bool Chessboard::isEmpty(Point point) {
    int piece = getPiece(point);
    return piece==0;
}

int Chessboard::getHeight() {
    return board.size();
}

int Chessboard::getWidth() {
    return board[0].size();
}

int Chessboard::getPieceCount() {
    int cnt=0;
    for(int y=0;y<board.size();y++)
        for(int x=0;x<board[0].size();x++){
            if(getPiece({x,y})!=0){
                cnt++;
            }
        }
    return cnt;
}

int Chessboard::getPiece(Point point) {
    if(point.x<getWidth()&&point.x>=0&&point.y<getHeight()&&point.y>=0)
        return board[point.y][point.x].num;
    else
        return -1;
}

int Chessboard::setPiece(Point point, int num) {
    int last = getPiece(point);
    if(last!=-1){
        board[point.y][point.x].num=num;
    }
    return last;
}

///////////////////

bool Chessboard::merge_UP() {
    bool ans = false;
    for(int y=1;y<getHeight();y++){
        for(int x=0;x<getWidth();x++){
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x,y-i});
                for(;next==0;i++,next = getPiece({x,y-i}));
                if(next==piece&&board[y-i][x].flag== false){
                    board[y-i][x].num+=piece;
                    board[y-i][x].flag= true;
                    board[y][x].num=0;
                    ans= true;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::canSlide_UP() {
    bool ans = false;
    for(int y=1;y<getHeight();y++){
        for(int x=0;x<getWidth();x++){
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x,y-i});
                for(;next==0;i++,next = getPiece({x,y-i}));
                if(next==piece&&board[y-i][x].flag== false){
                    ans= true;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::land_UP() {
    bool ans = false;
    for(int y=1;y<getHeight();y++){
        for(int x=0;x<getWidth();x++){
            board[y][x].flag= false;
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x,y-i});
                for(;next==0;i++,next = getPiece({x,y-i}));
                if(i>1){
                    ans = true;
                    board[y][x].num=0;
                    board[y-(i-1)][x].num=piece;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::merge_DOWN() {
    bool ans = false;
    for(int y=getHeight()-1;y>=0;y--){
        for(int x=0;x<getWidth();x++){
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x,y+i});
                for(;next==0;i++,next = getPiece({x,y+i}));
                if(next==piece&&board[y+i][x].flag== false){
                    board[y+i][x].num+=piece;
                    board[y+i][x].flag= true;
                    board[y][x].num=0;
                    ans= true;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::canSlide_DOWN() {
    bool ans = false;
    for(int y=getHeight()-1;y>=0;y--){
        for(int x=0;x<getWidth();x++){
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x,y+i});
                for(;next==0;i++,next = getPiece({x,y+i}));
                if(next==piece&&board[y+i][x].flag== false){
                    ans= true;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::land_DOWN() {
    bool ans = false;
    for(int y=getHeight()-1;y>=0;y--){
        for(int x=0;x<getWidth();x++){
            board[y][x].flag= false;
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x,y+i});
                for(;next==0;i++,next = getPiece({x,y+i}));
                if(i>1){
                    ans = true;
                    board[y][x].num=0;
                    board[y+(i-1)][x].num=piece;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::merge_LEFT() {
    bool ans = false;
    for(int x=0;x<getWidth();x++){
        for(int y=0;y<getHeight();y++){
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x-i,y});
                for(;next==0;i++,next = getPiece({x-i,y}));
                if(next==piece&&board[y][x-i].flag== false){
                    board[y][x-i].num+=piece;
                    board[y][x-i].flag= true;
                    board[y][x].num=0;
                    ans= true;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::canSlide_LEFT() {
    bool ans = false;
    for(int x=0;x<getWidth();x++){
        for(int y=0;y<getHeight();y++){
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x-i,y});
                for(;next==0;i++,next = getPiece({x-i,y}));
                if(next==piece&&board[y][x-i].flag== false){
                    ans= true;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::land_LEFT() {
    bool ans = false;
    for(int x=0;x<getWidth();x++){
        for(int y=0;y<getHeight();y++){
            board[y][x].flag= false;
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x-i,y});
                for(;next==0;i++,next = getPiece({x-i,y}));
                if(i>1){
                    ans = true;
                    board[y][x].num=0;
                    board[y][x-(i-1)].num=piece;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::merge_RIGHT() {
    bool ans = false;
    for(int x=getWidth()-1;x>=0;x--){
        for(int y=0;y<getHeight();y++){
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x+i,y});
                for(;next==0;i++,next = getPiece({x+i,y}));
                if(next==piece&&board[y][x+i].flag== false){
                    board[y][x+i].num+=piece;
                    board[y][x+i].flag= true;
                    board[y][x].num=0;
                    ans= true;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::canSlide_RIGHT() {
    bool ans = false;
    for(int x=getWidth()-1;x>=0;x--){
        for(int y=0;y<getHeight();y++){
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x+i,y});
                for(;next==0;i++,next = getPiece({x+i,y}));
                if(next==piece&&board[y][x+i].flag== false){
                    ans= true;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::land_RIGHT() {
    bool ans = false;
    for(int x=getWidth()-1;x>=0;x--){
        for(int y=0;y<getHeight();y++){
            board[y][x].flag= false;
            int piece = getPiece({x,y});
            if(piece!=0&&piece!=-1){
                int i=1,next = getPiece({x+i,y});
                for(;next==0;i++,next = getPiece({x+i,y}));
                if(i>1){
                    ans = true;
                    board[y][x].num=0;
                    board[y][x+(i-1)].num=piece;
                }
            }
        }
    }
    return ans;
}

bool Chessboard::canSlide() {
    return canSlide_UP()||canSlide_DOWN()||canSlide_LEFT()||canSlide_RIGHT();
}

bool Chessboard::slide_UP() {
    bool ans = merge_UP();
    land_UP();
    return ans;
}

bool Chessboard::slide_DOWN() {
    bool ans = merge_DOWN();
    land_DOWN();
    return ans;
}

bool Chessboard::slide_LEFT() {
    bool ans = merge_LEFT();
    land_LEFT();
    return ans;
}

bool Chessboard::slide_RIGHT() {
    bool ans = merge_RIGHT();
    land_RIGHT();
    return ans;
}

int Chessboard::getMaxPiece() {
    int ans=0;
    for(int y=0;y<getHeight();y++){
        for(int x=0;x<getWidth();x++){
            ans = std::max(ans,getPiece({x,y}));
        }
    }
    return ans;
}