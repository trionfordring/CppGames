//
// Created by fordring on 2020/5/2.
//

#ifndef CPPGAMES_FORWARD_H
#define CPPGAMES_FORWARD_H

#include "Point.h"


//typedef void (Callback)(Point point, const Forward& forward);
//template <typename Callback>
//typedef void (*Foreach)(Point a, Point b, Callback callback);


template <typename F>
class Forward {
public:
    int x_offset,y_offset;
    Forward(int x_offset,int y_offset);
    virtual void foreach(Point a, Point b, F callback)=0;
};


extern const Forward UP_FORWARD;
extern const Forward DOWN_FORWARD;
extern const Forward LEFT_FORWARD;
extern const Forward RIGHT_FORWARD;

Point offset(Point point,const Forward& forward,int step=1);

#endif //CPPGAMES_FORWARD_H
