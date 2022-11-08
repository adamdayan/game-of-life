#include <iostream>
#include <chrono>
#include <thread>
#include "game_manager.h"
#include "board.h"
#include "renderer.h"
#include "exceptions.h"



void GameManager::play() {
    board->setRandomSeed(); // TODO: add manual seed
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