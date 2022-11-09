#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <memory>
#include <vector>
#include "board.h"
#include "renderer.h"

class GameManager {
  public:
    GameManager(int size, bool is_rendered, bool is_gpu, int delay = 0, std::string board_path = "") : size(size), is_rendered(is_rendered), is_gpu(is_gpu), delay(delay), board_path(board_path) {
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
    std::vector<std::vector<int>> loadBoard();
    void saveBoard(std::vector<std::vector<int>> seed_board);
  private:
    int size;
    bool is_rendered;
    bool is_gpu;
    int delay;
    std::string board_path;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Board> board;
};

#endif