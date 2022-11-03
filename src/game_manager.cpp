#include <iostream>
#include "game_manager.h"
#include "board.h"
#include "renderer.h"
#include "exceptions.h"

void GameManager::play() {
    board.setRandomSeed(); // TODO: add manual seed
    while (true) {
        if (is_rendered) {
            try {
                renderer.drawBoard(board.getBoard(), board.getGeneration());
            } catch (ClosedWindowException& cwe) {
                std::cout << "User closed window";
                return;
            }
        }
        board.evolve();
    }
}