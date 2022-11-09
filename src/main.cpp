#include "game_manager.h"

int main() {
    GameManager game_manager(400, true, true, 5, "data/board.txt");
    game_manager.play();
    return 0;
}