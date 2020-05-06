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
:rand4Rate((int)(DEFAULT_RAND_4_RATE*RAND_MAX)),
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
 cellBackground(CELL_BACKGROUND),
 helpText(DEFAULT_STRING_HELP),
 startMenu{startText,helpText,exitText},
 continueMenu{continueText,helpText,newGameText,exitText}
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
    srand(clock());
    chessboard = Chessboard(chessboardWidth,chessboardHeight);
    for(int i=0;i<initPieceNum;i++){
        chessboard.insertPiece(randomEmptyPoint(),randomPiece());
    }
}

int Game2048::randomPiece() {
    int r = rand();
    return r>rand4Rate?2:4;
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

int Game2048::menuScreen() {
    cleanConsole();
    int selected = 0;
    std::vector<string> menu=startMenu;
    auto gameScreenHandle = [&]()->int {
        int ans = gameScreen();
        cleanConsole();
        selected=0;
        if(ans==1){
            gameOverScreen();
            menu=startMenu;
            return 1;
        }
        return 0;
    };
    int c;
    while(true){
        drawTitle(titlePosition);
        drawMenu(menuPosition, selected, menu);
        c = read();
       switch (c){
           case 'a':
           case 'w':
               selected--;
               selected = abs(selected);
               selected%=menu.size();
               drawMenu(menuPosition, selected, menu);
               break;
           case 's':
           case 'd':
               selected++;
               selected = abs(selected);
               selected%=menu.size();
               drawMenu(menuPosition, selected, menu);
               break;
           case 13:
               if(menu[selected] == exitText){
                   return 0;
               }else if(menu[selected] == startText){
                   menu=continueMenu;
                   gameScreenHandle();
               }else if(menu[selected] == continueText){
                   gameScreenHandle();
               }else if(menu[selected] == newGameText){
                   initChessboard();
                   gameScreenHandle();
               }else if(menu[selected] == helpText){
                   helpScreen();
               }
               break;
           case 27:
               return 0;
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

int Game2048::gameScreen() {
    cleanConsole();
    showText(textPosition,"  use 'esc' to back to enum,use 'w''a''s''d' to slide chessboard.");
    int c;
    bool ans;
    while(true){
        drawChessboard(initPoint);
        if(chessboard.getPieceCount()==chessboard.getHeight()*chessboard.getWidth()&&!chessboard.canSlide()){
            return 1;
        }
        c=read();
        switch (c){
            case 27:
                return 0;
            case 'w':
                ans = chessboard.slide_UP();
                break;
            case 'a':
                ans = chessboard.slide_LEFT();
                break;
            case 's':
                ans = chessboard.slide_DOWN();
                break;
            case 'd':
                ans = chessboard.slide_RIGHT();
                break;
        }
        if(ans){
            randomInsertPiece();
            std::ostringstream oss;
            oss<<" nice! your max num is "<<chessboard.getMaxPiece();
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


int Game2048::gameOverScreen() {
    cleanConsole();
    drawTitle(titlePosition);
    int num = chessboard.getMaxPiece();
    std::ostringstream oss;
    oss<<"YOUR MAX NUMBER IS "<<num<<". ";
    if(num<=16){
        oss<<"HOW CAN YOU GET IT?";
    }else if(num<=128){
        oss<<"HOW STUPID YOU ARE?";
    }else if(num<=512){
        oss<<"JUST SO SO.";
    }else if(num<=1024){
        oss<<"emmm..OK..OK.";
    }else if(num<=2048){
        oss<<"NICE.";
    }else{
        oss<<"BE HONEST?";
    }
    std::vector<string> str{"        GAME OVER!",
                            oss.str(),
                            "",
                            " PRESS KEY 'enter'or'esc' TO BACK TO MENU."
    };
    draw(menuPosition,str);
    initChessboard();
    int a = read();
    while(a!=13&&a!=27)a=read();
    cleanConsole();
    return 0;
}

int Game2048::helpScreen() {
    cleanConsole();
    drawTitle(titlePosition);
    std::vector<string> str{"HELP:",
                            "1. press 'W''A''S''D' to slide all the pieces.",
                            "2. pieces will move if next cell is empty or same.",
                            "3. same number will merge and be a bigger num.",
                            "4. try your best to get a larger number!",
                            "",
                            "  PRESS ANY KEY TO BACK"
    };
    draw(menuPosition,str);
    read();
    cleanConsole();
    return 0;
}