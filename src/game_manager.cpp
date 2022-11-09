#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include "game_manager.h"
#include "board.h"
#include "renderer.h"
#include "exceptions.h"



// assumes saved board will follow format of:
// 0 0 1 1
// 1 0 0 1
// 0 1 1 1
// 1 0 0 0
std::vector<std::vector<int>> GameManager::loadBoard() {
    std::ifstream board_file(board_path);
    std::vector<std::vector<int>> seed_board;
    for (int i = 0; i < size; i++) {
        std::string line;
        getline(board_file, line);
        std::vector<int> row;
        for (int j = 0; j < size; j++) {
            row.push_back(std::stoi(line.substr(j*2, j*2+1)));
        }
        seed_board.push_back(row);
    }
    return seed_board;
}

void GameManager::saveBoard(std::vector<std::vector<int>> seed_board) {
    std::ofstream board_file("data/board.txt");
    for (auto row : seed_board) {
        std::string line;
        for (auto cell : row) {
            line+= std::to_string(cell) + " ";
        }
        board_file << line << std::endl;
    }
}

void GameManager::play() {
    if (board_path.empty()) {
        board->setRandomSeed();
        saveBoard(board->getBoard());
    } else {
        board->setManualSeed(loadBoard());
    }
    while (true) {
        if (is_rendered) {
            try {
                renderer->drawBoard(board->getBoard(), board->getGeneration());
            } catch (ClosedWindowException& cwe) {
                std::cout << "User closed window";
                return;
            }
        }
        if (delay) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
        board->evolve();
    }
}

void GameManager::play(int n_generations) {
    board->setRandomSeed();
    int cur_generation = board->getGeneration();
    while (cur_generation < n_generations) {
        if (is_rendered) {
            try {
                renderer->drawBoard(board->getBoard(), cur_generation);
            } catch (ClosedWindowException& cwe) {
                std::cout << "User closed window";
                return;
            }
        }
        if (delay) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
        board->evolve();
        cur_generation = board->getGeneration();
    }
}