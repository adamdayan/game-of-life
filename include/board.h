#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

class Board {
  public:
    Board(int size) : size(size) {}
    int getGeneration() {return generation;};
    virtual std::vector<std::vector<int>> getBoard() = 0;
    virtual void setManualSeed(const std::vector<std::vector<int>>& seed_board) = 0; // NOTE: potentially want to use a binary number as seed that represents board state
    virtual void setRandomSeed() = 0;
    virtual void evolve() = 0;
  protected:
    int size;
    int generation = 0;
};

class CPUBoard : public Board {
  using Board::Board;
  public:
    std::vector<std::vector<int>> getBoard() override; 
    void setManualSeed(const std::vector<std::vector<int>>& seed_board) override;
    void setRandomSeed() override;
    void evolve() override;
  private:
    int computeAliveNeighbourCnt(const int x, const int y);
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> old_board;
};

class GPUBoard : public Board {
  using Board::Board;
  public:
    std::vector<std::vector<int>> getBoard() override;
    void setManualSeed(const std::vector<std::vector<int>>& seed_board) override;
    void setRandomSeed() override;
    void evolve() override;
  private:
    thrust::device_vector<int> board; //= thrust::device_vector<int>(size*size);
    thrust::device_vector<int> old_board; // = thrust::device_vector<int>(size*size);

  // TODO: add thrust vector (try in this file but potentially means different file)
  // + write code in board.cu (!) 

  // NOTE - unclear this will cause significant speed up cos of copying around
  // however I think if no one calls getBoard() then we can avoid moving data from device_vector to host_vector
};

#endif