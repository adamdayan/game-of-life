#include <vector>
#include <gtest/gtest.h>
#include "board.h"

TEST(TestCPUBoard, TestsetManualSeed) {
    CPUBoard board = CPUBoard(4);
    std::vector<std::vector<int>> seed_board(4, std::vector<int>(4, 0));
    board.setManualSeed(seed_board); 
    ASSERT_EQ(board.getBoard(), seed_board);
}

TEST(TestCPUBoard, TestBlinker) {
    CPUBoard board = CPUBoard(4);
    std::vector<std::vector<int>> seed_board = {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
    };
    board.setManualSeed(seed_board);
    board.evolve();
    std::vector<std::vector<int>> correct_output_board = {
        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    };
    ASSERT_EQ(board.getBoard(), correct_output_board);
}

TEST(TestCPUBoard, TestBoardCorners) {
    CPUBoard board = CPUBoard(4);
    std::vector<std::vector<int>> seed_board = {
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 1},
    };
    board.setManualSeed(seed_board);
    board.evolve();
    ASSERT_EQ(board.getBoard(), seed_board);
}

TEST(TestCPUBoard, TestBoardOvercrowding) {
    CPUBoard board = CPUBoard(4);
    std::vector<std::vector<int>> seed_board = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
    };
    board.setManualSeed(seed_board);
    board.evolve();
    std::vector<std::vector<int>> correct_output_board = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    };
    ASSERT_EQ(board.getBoard(), correct_output_board);
}