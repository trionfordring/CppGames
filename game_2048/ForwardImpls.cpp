//
// Created by fordring on 2020/5/3.
//

#include "ForwardImpls.h"

//
// Created by fordring on 2020/5/2.
//
#include "Forward.h"

//up
template <typename F>
void UpForward<F>::foreach(Point a, Point b, F callback) {
    for(int y=b.y;y<=a.y;y++){
        for(int x=a.x;x<=b.x;x++){
            callback({x,y},UP_FORWARD);
        }
    }
}

template <typename F>
UpForward<F>::UpForward(int x_offset,int y_offset): Forward<F>(x_offset,y_offset){
}

const Forward UP_FORWARD = UpForward(0,-1);

//down
template <typename F>
void DownForward::foreach(Point a, Point b, F callback) {
    for(int y=a.y;y>=b.y;y--){
        for(int x=a.x;x<=b.x;x++){
            callback({x,y},DOWN_FORWARD);
        }
    }
}

DownForward::DownForward(int x_offset, int y_offset): Forward(x_offset,y_offset) {}
const Forward DOWN_FORWARD = DownForward(0,1);


//left
template <typename F>
void LeftForward::foreach(Point a, Point b,F callback){
    for(int x=a.x;x<=b.x;x++){
        for(int y=b.y;y<=a.y;y++) {
            callback({x,y},LEFT_FORWARD);
        }
    }
}

LeftForward::LeftForward(int x_offset, int y_offset): Forward(x_offset,y_offset) {}

const Forward LEFT_FORWARD = LeftForward(1,0);

//right
template <typename F>
void RightForward::foreach(Point a, Point b,F callback){
    for(int x=b.x;x>=a.x;x--){
        for(int y=b.y;y<=a.y;y++) {
            callback({x,y},RIGHT_FORWARD);
        }
    }
}

RightForward::RightForward(int x_offset, int y_offset): Forward(x_offset,y_offset)  {}

const Forward RIGHT_FORWARD = RightForward(1,0);

Point offset(Point point,const Forward& forward, int step){
    return {.x=point.x+forward.x_offset*step,.y=point.y+forward.y_offset*step};
}