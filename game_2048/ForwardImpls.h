//
// Created by fordring on 2020/5/3.
//

#ifndef CPPGAMES_FORWARDIMPLS_H
#define CPPGAMES_FORWARDIMPLS_H

#include "Forward.h"

template <typename F>
class UpForward : public Forward<F>{
public:
    UpForward(int x_offset,int y_offset);
    void foreach(Point a, Point b, F callback);
};
template <typename F>
class DownForward : public Forward{
public:
    DownForward(int x_offset,int y_offset);
    void foreach(Point a, Point b, F callback);
};
template <typename F>
class LeftForward : public Forward{
public:
    LeftForward(int x_offset,int y_offset);
    void foreach(Point a, Point b, F callback);
};
template <typename F>
class RightForward : public Forward{
public:
    RightForward(int x_offset,int y_offset);
    void foreach(Point a, Point b, F callback);
};


#endif //CPPGAMES_FORWARDIMPLS_H
