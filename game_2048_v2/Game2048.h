//
// Created by fordring on 2020/5/3.
//

#ifndef CPPGAMES_GAME2048_H
#define CPPGAMES_GAME2048_H

#include <string>
#include <vector>
#include <wincon.h>
#include "Point.h"
#include "Chessboard.h"

using std::string;

const std::vector<string> DEFAULT_TITLE{
        "  _______  ________  ___   ___  ________     ",
       R"( /  ___  \|\   __  \|\  \ |\  \|\   __  \    )",
       R"(/__/|_/  /\ \  \|\  \ \  \\_\  \ \  \|\  \   )",
       R"(|__|//  / /\ \  \\\  \ \______  \ \   __  \  )",
       R"(    /  /_/__\ \  \\\  \|_____|\  \ \  \|\  \ )",
       R"(   |\________\ \_______\     \ \__\ \_______\)",
       R"(    \|_______|\|_______|      \|__|\|_______|)"
};
const std::vector<string> BACKUP_TITLE{
    "  ___   ___  _  _   ___  ",
    R"( |__ \ / _ \| || | / _ \ )",
    "    ) | | | | || || (_) |",
    "   / /| | | |__   _> _ < ",
    "  / /_| |_| |  | || (_) |",
    " |____|\\___/   |_| \\___/ "
};

const std::vector<string> BACKGROUND{
    " ____________________________ ",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|                            |",
    "|____________________________|"
};

const std::vector<string> CELL_BACKGROUND{
        " _____ ",
        "|     |",
        "|     |",
        "|_____|"
};

const float DEFAULT_RAND_4_RATE=0.25;
const int DEFAULT_CHESSBOARD_INIT_PIECE_NUM=2;
const int DEFAULT_CHESSBOARD_WIDTH=4;
const int DEFAULT_CHESSBOARD_HEIGHT=4;
const int DEFAULT_CHESSBOARD_BORDER=1;
const int DEFAULT_CELL_WIDTH=7;
const int DEFAULT_CELL_HEIGHT=4;
const int DEFAULT_NUMBER_SHOW_POSITION_X=2;
const int DEFAULT_NUMBER_SHOW_POSITION_Y=2;
const int DEFAULT_INIT_CURSOR_POSITION_X=0;
const int DEFAULT_INIT_CURSOR_POSITION_Y=0;
const int DEFAULT_TITLE_CURSOR_POSITION_X=DEFAULT_INIT_CURSOR_POSITION_X+6;
const int DEFAULT_TITLE_CURSOR_POSITION_Y=DEFAULT_INIT_CURSOR_POSITION_Y;
const int DEFAULT_MENU_CURSOR_POSITION_X=DEFAULT_TITLE_CURSOR_POSITION_X+1;
const int DEFAULT_MENU_CURSOR_POSITION_Y=DEFAULT_TITLE_CURSOR_POSITION_Y+DEFAULT_TITLE.size()+2;
const int DEFAULT_TEXT_CURSOR_POSITION_X=DEFAULT_INIT_CURSOR_POSITION_X;
const int DEFAULT_TEXT_CURSOR_POSITION_Y=DEFAULT_INIT_CURSOR_POSITION_Y+DEFAULT_CHESSBOARD_BORDER*2+DEFAULT_CHESSBOARD_HEIGHT*DEFAULT_CELL_HEIGHT+1;
const int DEFAULT_BUFFER_COORD_X = 100;
const int DEFAULT_BUFFER_COORD_Y = 100;

const string DEFAULT_STRING_START       = "> start ";
const string DEFAULT_STRING_CONTINUE    = "> continue ";
const string DEFAULT_STRING_SETTING     = "> setting ";
const string DEFAULT_STRING_NEW_GAME    = "> new game ";
const string DEFAULT_STRING_EXIT        = "> exit ";
const string DEFAULT_STRING_HELP        = "> help ";


const int DEFAULT_MENU_SELECTED_COLOR    =  BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

class Game2048 {
private:
public :
    int rand4Rate;
    Point initPoint;
    Point textPosition;
    Point menuPosition;
    Point numShowPosition;
    Point titlePosition;
    Point bufferSize;
    int border;
    int cellWidth;
    int cellHeight;
    int menuSelectedColor;
    int chessboardWidth;
    int chessboardHeight;
    int initPieceNum;
    std::vector<std::string> title;
    std::vector<std::string> background;
    std::vector<std::string> cellBackground;
    Chessboard chessboard;

    string startText;
    string exitText;
    string settingText;
    string newGameText;
    string continueText;
    string helpText;

    std::vector<std::string> startMenu;
    std::vector<std::string> continueMenu;
    void initChessboard();
    Point randomPoint();
    Point randomEmptyPoint();
    int randomPiece();
    bool randomInsertPiece();
    void drawTitle(Point point);
    void drawMenu(Point point,int select,const std::vector<string>& menu);
    void drawChessboard(Point point);

    int menuScreen();
    int gameScreen();
    int gameOverScreen();
    int helpScreen();


public:
    Game2048();
    void init(int cursorSize=1,bool cursorVisible= false);
    void start();
    void showText(Point p,const string& msg);
    void cleanConsole();

};


#endif //CPPGAMES_GAME2048_H
