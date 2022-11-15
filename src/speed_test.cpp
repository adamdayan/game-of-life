#include <vector>
#include <chrono>
#include "game_manager.h"


int main() {
    std::vector<int> sizes{100, 1000, 10000};
    for (int size : sizes) {
        std::cout << "size: " << size << std::endl;
        GameManager cpu_gm(size, false, false);
        auto start = std::chrono::steady_clock::now();
        cpu_gm.play(1000);
        auto end = std::chrono::steady_clock::now();
        auto cpu_diff = end - start;

        GameManager gpu_gm(size, false, true);
        start = std::chrono::steady_clock::now();
        gpu_gm.play(1000);
        end = std::chrono::steady_clock::now();
        auto gpu_diff = end - start;

        std::cout << "cpu: " << std::chrono::duration <double, std::milli>(cpu_diff).count() << "ms" 
            << " gpu: " << std::chrono::duration <double, std::milli>(gpu_diff).count() << "ms" << std::endl << std::endl;
    }
}