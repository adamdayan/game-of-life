#include <stdexcept>
#include <random>
#include <vector>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

#include "board.h"

__device__ int get_remainder_gpu(int dividend, int divisor) {
    return (dividend % divisor + divisor) % divisor;
}

std::vector<std::vector<int>> GPUBoard::getBoard() {
    std::vector<std::vector<int>> standardised_board;
    thrust::host_vector<int> tmp_host_board = board;
    for (int i = 0; i < size; i++) {
        std::vector<int> row;
        for (int j = 0; j < size; j++) {
            row.push_back(tmp_host_board[(i*size)+j]);
        }
        standardised_board.push_back(row);
    }
    return standardised_board;
}

void GPUBoard::setManualSeed(const std::vector<std::vector<int>>& seed_board) {
    for (auto row : seed_board) {
        for (auto cell : row) {
            board.push_back(cell);
        }
    }
}

void GPUBoard::setRandomSeed() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,1);
    thrust::host_vector<int> tmp_host_vector;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tmp_host_vector.push_back(distribution(generator));
        }
    }
    board = tmp_host_vector;
}

__device__ int compute_alive_neighbour_cnt(const int x, const int y, const int size, const int* old_board) {
    int cnt_alive_neighbours = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int idx = (get_remainder_gpu(x - 1 + i, size)*size) + get_remainder_gpu(y - 1 + j, size);
            if ((old_board[idx] == 1) && (!(i == 1 && j == 1))) {
                cnt_alive_neighbours++;
            }
        }
    }
    return cnt_alive_neighbours;
}

__global__ void evolve_board(int size, int* board, int* old_board) {
    int idx = (blockIdx.x * blockDim.x) + threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    for (int i = idx; i < size*size; i+=stride) {
        int row = i / size;
        int col = i % size;
        int alive_neighbour_cnt = compute_alive_neighbour_cnt(row, col, size, old_board);
        if (old_board[i] == 1 && alive_neighbour_cnt < 2) { // dies from underpopulation
            board[i] = 0;
        } else if (old_board[i] == 1 && alive_neighbour_cnt > 3) {// dies from overcrowding
            board[i] = 0;
        } else if (old_board[i] == 0 && alive_neighbour_cnt == 3) { // birth
            board[i] = 1;
        }
    }   
}

void GPUBoard::evolve() {
    generation++;
    int block_size= 256;
    int num_blocks= ((size*size) + block_size - 1) / block_size;
    //thrust::copy(board.begin(), board.end(), old_board.begin());
    old_board = board;
    evolve_board<<<num_blocks, block_size>>>(
        size, thrust::raw_pointer_cast(board.data()), thrust::raw_pointer_cast(old_board.data())
    );    
}