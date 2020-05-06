#include "game_2048_v2/Game2048.h"
#include <iostream>
using std::cout,std::endl;
int main() {
    Game2048 game2048;
    game2048.init(1, false);
    game2048.start();
    return 0;
}