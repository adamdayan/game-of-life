#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
  public:
    Board(int size) : size(size) {}
    std::vector<std::vector<int>> getBoard(); // NOTE: do I want to be returning a copy of the board
    void setManualSeed(const std::vector<std::vector<int>>& seed_board); // NOTE: potentially want to use a binary number as seed that represents board state
    void setRandomSeed();
    int getGeneration() {return generation;};
    void evolve();
  private:
    int computeAliveNeighbourCnt(const int x, const int y);
    int size;
    int generation = 0;
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> old_board;
};
#endif