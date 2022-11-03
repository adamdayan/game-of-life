#include <stdexcept>
#include <random>
#include <vector>
#include "board.h"

int get_remainder(int dividend, int divisor) {
    return (dividend % divisor + divisor) % divisor;
}


std::vector<std::vector<int>> Board::getBoard() {
    return board;
}

void Board::setManualSeed(const std::vector<std::vector<int>>& seed_board) {
    if (static_cast<int>(seed_board.size()) != size) {
        throw std::invalid_argument("Seed board is wrong size");
    }
    for (auto row : seed_board) {
        if (static_cast<int>(row.size()) != size) {
            throw std::invalid_argument("Seed board is wrong size");
        }
    }
    board = seed_board;
}

void Board::setRandomSeed() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,1);
    for (int i = 0; i < size; i++) {
        std::vector<int> row;
        for (int j = 0; j < size; j++) {
            row.push_back(distribution(generator));
        }
        board.push_back(row);
    }
}

int Board::computeAliveNeighbourCnt(const int x, const int y) {
    int cnt_alive_neighbours = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((old_board[get_remainder(x - 1 + i, size)][get_remainder(y - 1 + j, size)] == 1) && (!(i == 1 && j == 1))) {
                cnt_alive_neighbours++;
            }
        }
    }
    return cnt_alive_neighbours;
}

void Board::evolve() {
    old_board = board;
    generation++;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int cnt_alive_neighbours = computeAliveNeighbourCnt(i, j);
            // TODO: write new board
            if (board[i][j] == 1 && cnt_alive_neighbours < 2) { // dies by underpopulation
                board[i][j] = 0;
            } else if (board[i][j] == 1 && cnt_alive_neighbours > 3) { // dies by overpo
                board[i][j] = 0;
            } else if (board[i][j] == 0 && cnt_alive_neighbours == 3) { // born by reproduction
                board[i][j] = 1;
            }
        }
    }
}

