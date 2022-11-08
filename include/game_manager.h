#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <memory>
#include "board.h"
#include "renderer.h"

class GameManager {
  public:
    GameManager(int size, bool is_rendered, bool is_gpu, int delay = 0) : size(size), is_rendered(is_rendered), is_gpu(is_gpu), delay(delay) {
      if (is_rendered) {
        renderer = std::make_unique<Renderer>(size);
      }

      if (is_gpu) {
        board = std::make_unique<GPUBoard>(size);
      } else {
        board = std::make_unique<CPUBoard>(size);
      }
    };
    void play();
    void play(int n_generations);
  private:
    int size;
    bool is_rendered;
    bool is_gpu;
    int delay;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Board> board;
};

#endif