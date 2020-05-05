#include "game_2048_v2/Game2048.h"
#include <iostream>
int main() {
    Game2048 game2048;
    game2048.init(1, false);
    game2048.start();
    return 0;
}