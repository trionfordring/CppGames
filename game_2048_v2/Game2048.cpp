//
// Created by fordring on 2020/5/3.
//

#include "Game2048.h"
#include <windows.h>
#include <random>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <sstream>

using std::cout;


Game2048::Game2048()
:rand4Rate(DEFAULT_RAND_4_RATE*RAND_4_RATE_ACCURACY),
 initPieceNum(DEFAULT_CHESSBOARD_INIT_PIECE_NUM),
 initPoint{DEFAULT_INIT_CURSOR_POSITION_X,DEFAULT_INIT_CURSOR_POSITION_Y},
 cellWidth(DEFAULT_CELL_WIDTH),
 cellHeight(DEFAULT_CELL_HEIGHT),
 numShowPosition{DEFAULT_NUMBER_SHOW_POSITION_X,DEFAULT_NUMBER_SHOW_POSITION_Y},
 chessboardWidth(DEFAULT_CHESSBOARD_WIDTH),
 chessboardHeight(DEFAULT_CHESSBOARD_HEIGHT),
 border(DEFAULT_CHESSBOARD_BORDER),
 textPosition{DEFAULT_TEXT_CURSOR_POSITION_X,DEFAULT_TEXT_CURSOR_POSITION_Y},
 menuPosition{DEFAULT_MENU_CURSOR_POSITION_X,DEFAULT_MENU_CURSOR_POSITION_Y},
 title(DEFAULT_TITLE),
 titlePosition{DEFAULT_TITLE_CURSOR_POSITION_X,DEFAULT_TITLE_CURSOR_POSITION_Y},
 bufferSize{DEFAULT_BUFFER_COORD_X,DEFAULT_BUFFER_COORD_Y},
 menuSelectedColor(DEFAULT_MENU_SELECTED_COLOR),
 startText(DEFAULT_STRING_START),
 exitText(DEFAULT_STRING_EXIT),
 settingText(DEFAULT_STRING_SETTING),
 newGameText(DEFAULT_STRING_NEW_GAME),
 continueText(DEFAULT_STRING_CONTINUE),
 background(BACKGROUND),
 cellBackground(CELL_BACKGROUND)
{}

static HANDLE STD_OUT;
COORD point2COORD(Point point){
    return {(short)point.x,(short)point.y};
}

void draw(Point point,const std::vector<string> str){
    COORD p = point2COORD(point);
    for(int i=0;i<str.size();i++){
        COORD t = p;
        t.Y+=i;
        SetConsoleCursorPosition(STD_OUT,t);
        cout<<str[i];
    }
    SetConsoleCursorPosition(STD_OUT,p);
}

void Game2048::init(int cursorSize,bool cursorVisible) {
    srand(clock());
    cleanConsole();
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize=cursorSize,cursorInfo.bVisible=cursorVisible;
    STD_OUT = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position=point2COORD(initPoint);
    SetConsoleCursorInfo(STD_OUT,&cursorInfo);
    SetConsoleCursorPosition(STD_OUT,position);
    SetConsoleScreenBufferSize(STD_OUT,point2COORD(bufferSize));
    initChessboard();
}

void Game2048::initChessboard() {
    chessboard = Chessboard(chessboardWidth,chessboardHeight);
    for(int i=0;i<initPieceNum;i++){
        chessboard.insertPiece(randomEmptyPoint(),randomPiece());
    }
}

int Game2048::randomPiece() {
    return (rand()%RAND_4_RATE_ACCURACY)>rand4Rate?2:4;
}

Point Game2048::randomEmptyPoint() {
    Point point = randomPoint();
    while(chessboard.getPiece(point)!=0)point=randomPoint();
    return point;
}

Point Game2048::randomPoint() {
    int width=chessboard.getWidth(),height=chessboard.getHeight();
    return {rand()%width,rand()%height};
}

void Game2048::cleanConsole() {
    system("cls");
}

int read(){
    int ans = getch();
    if(ans<=0||ans>=128)ans=getch();
    switch (ans){
        case 72:
            ans='w';
            break;
        case 80:
            ans='s';
            break;
        case 75:
            ans='a';
            break;
        case 77:
            ans='d';
            break;
    }
    return ans;
}

void Game2048::drawTitle(Point point) {
    COORD p = point2COORD(point);
    for(int i=0;i<title.size();i++){
        COORD t = p;
        t.Y+=i;
        SetConsoleCursorPosition(STD_OUT,t);
        cout<<title[i];
    }
    SetConsoleCursorPosition(STD_OUT,p);
}

void Game2048::drawMenu(Point point, int select,const std::vector<string>& menu) {
    COORD p = point2COORD(point);
    select = abs(select);
    select%=menu.size();
    for(int i=0;i<menu.size();i++){
        COORD t = p;
        t.Y+=i;
        SetConsoleCursorPosition(STD_OUT,t);
        if(select==i){
            SetConsoleTextAttribute(STD_OUT,menuSelectedColor);
        }
        cout<<menu[i];
        if(select==i){
            SetConsoleTextAttribute(STD_OUT,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
        }
    }
}

void Game2048::start() {
    menuScreen();
}

void Game2048::menuScreen() {
    cleanConsole();
    drawTitle(titlePosition);
    int selected = 0;
    std::vector<string> initMenu{startText,exitText};

    int c;
    while(true){
        drawMenu(menuPosition,selected,initMenu);
       c = read();
       switch (c){
           case 'a':
           case 'w':
               selected--;
               selected = abs(selected);
               selected%=initMenu.size();
               drawMenu(menuPosition,selected,initMenu);
               break;
           case 's':
           case 'd':
               selected++;
               selected = abs(selected);
               selected%=initMenu.size();
               drawMenu(menuPosition,selected,initMenu);
               break;
           case 13:
               if(initMenu[selected]==exitText){
                   return;
               }else if(initMenu[selected]==startText){
                   initMenu={continueText,newGameText,exitText};
                   gameScreen();
                   cleanConsole();
                   drawTitle(titlePosition);
                   selected=0;
               }else if(initMenu[selected]==continueText){
                   gameScreen();
                   cleanConsole();
                   drawTitle(titlePosition);
                   selected=0;
               }else if(initMenu[selected]==newGameText){
                    initChessboard();
                    gameScreen();
                   cleanConsole();
                   drawTitle(titlePosition);
                    selected=0;
               }
               break;
           case 27:
               return;
       }
    }
}

void Game2048::drawChessboard(Point point) {
    draw(initPoint,background);
    for(int y=0;y<chessboard.getHeight();y++){
        for(int x=0;x<chessboard.getWidth();x++){
            if(!chessboard.isEmpty({x,y})){
                Point p = {point.x+border+cellWidth*x,point.y+border+cellHeight*y};
                draw(p,cellBackground);
                p.x+=numShowPosition.x;
                p.y+=numShowPosition.y;
                SetConsoleCursorPosition(STD_OUT,point2COORD(p));
                cout<<chessboard.getPiece({x,y});
            }
        }
    }
}

void Game2048::gameScreen() {
    cleanConsole();
    showText(textPosition,"  use 'esc' to back to enum,use 'w''a''s''d' to slide chessboard.");
    int c;
    bool ans;
    while(true){
        drawChessboard(initPoint);
        c=read();
        switch (c){
            case 27:
                return;
            case 'w':
                ans = chessboard.slide_UP();
                randomInsertPiece();
                break;
            case 'a':
                ans = chessboard.slide_LEFT();
                randomInsertPiece();
                break;
            case 's':
                ans = chessboard.slide_DOWN();
                randomInsertPiece();
                break;
            case 'd':
                ans = chessboard.slide_RIGHT();
                randomInsertPiece();
                break;
        }
        if(ans){
            std::ostringstream oss;
            oss<<" nice! you max num is "<<chessboard.getMaxPiece();
            showText(textPosition,oss.str());
        }else{
            showText(textPosition," you can't move like this.");
        }
    }
}

void Game2048::showText(Point point,const string& msg){
    static int lastLength=0;
    COORD p = point2COORD(point);
    SetConsoleCursorPosition(STD_OUT,p);
    string space(lastLength,' ');
    cout<<space;
    lastLength=msg.length();
    SetConsoleCursorPosition(STD_OUT,p);
    cout<<msg;
}

bool Game2048::randomInsertPiece() {
    if(chessboard.getPieceCount()==chessboard.getWidth()*chessboard.getHeight()){
        return false;
    }
    return chessboard.insertPiece(randomEmptyPoint(),randomPiece());
}
