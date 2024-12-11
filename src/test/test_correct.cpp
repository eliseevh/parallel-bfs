#include "utils.h"
#include "../bfs.h"

constexpr size_t SIZE = 50;
constexpr size_t ITERS = 100;

void check(std::vector<size_t> const& distances) {
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            for (size_t k = 0; k < SIZE; k++) {
                if (distances[cube_index(i, j, k, SIZE)] != i + j + k) {
                    std::exit(1);
                }
            }
        }
    }
}

void main_seq(parlay::sequence<parlay::sequence<size_t>> const& cube) {
    std::cout << "Start testing seq..." << std::endl;
    for (size_t i = 0; i < ITERS; i++) {
        std::cout << "Run " << i + 1 << "/" << ITERS << std::endl;
        std::vector<size_t> distances = bfs_seq(0, cube);
        check(distances);
    }
}

void main_par(parlay::sequence<parlay::sequence<size_t>> const& cube) {
    std::cout << "Start testing par..." << std::endl;
    for (size_t i = 0; i < ITERS; i++) {
        std::cout << "Run " << i + 1 << "/" << ITERS << std::endl;
        std::vector<size_t> distances = bfs_par(0, cube);
        check(distances);
    }
}

int main() {
    parlay::sequence<parlay::sequence<size_t>> cube = gen_cube(SIZE);
    main_par(cube);
    main_seq(cube);
    std::cout << "Passed all" << std::endl;
}
