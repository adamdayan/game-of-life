#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "board.h"
#include "renderer.h"

class GameManager {
  public:
    GameManager(int size, bool is_rendered) : size(size), is_rendered(is_rendered) {}
    void play();
  private:
    int size;
    bool is_rendered;
    Renderer renderer = Renderer(size);
    Board board = Board(size);
};

#endif