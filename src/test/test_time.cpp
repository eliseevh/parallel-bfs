#include "utils.h"
#include "../bfs.h"

#include <sys/time.h>

constexpr size_t ITERS = 5;
constexpr size_t SIZE = 300;

time_t cur_time() {
    timeval tv = {};

    gettimeofday(&tv, nullptr);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

float main_seq(parlay::sequence<parlay::sequence<size_t>> const& cube) {
    time_t times[ITERS];
    std::cout << "Start running seq..." << std::endl;
    for (size_t i = 0; i < ITERS; ++i) {
        std::cout << "Run " << i + 1 << "/" << ITERS << std::endl;
        //parlay::sequence<parlay::sequence<size_t>> cube = gen_cube(SIZE);
        time_t start_it = cur_time();
        std::vector<size_t> distances = bfs_seq(0, cube);
        times[i] = cur_time() - start_it;
    }
    time_t times_sum = 0;
    std::cout << "Sequential times:";
    for (size_t i = 0; i < ITERS; ++i) {
        times_sum += times[i];
        std::cout << " " << times[i];
        if (i != ITERS - 1) {
            std::cout << ",";
        } else {
            std::cout << std::endl;
        }
    }
    float avg = static_cast<float>(times_sum) / ITERS;
    std::cerr << "Sequential average time: " << avg << std::endl;
    return avg;
}

float main_par(parlay::sequence<parlay::sequence<size_t>> const& cube) {
    time_t times[ITERS];
    std::cout << "Start running par..." << std::endl;
    for (size_t i = 0; i < ITERS; ++i) {
        std::cout << "Run " << i + 1 << "/" << ITERS << std::endl;
        time_t start_it = cur_time();
        std::vector<size_t> distances = bfs_par(0, cube);
        times[i] = cur_time() - start_it;
    }
    time_t times_sum = 0;
    std::cout << "Parallel times:";
    for (size_t i = 0; i < ITERS; ++i) {
        times_sum += times[i];
        std::cout << " " << times[i];
        if (i != ITERS - 1) {
            std::cout << ",";
        } else {
            std::cout << std::endl;
        }
    }
    float avg = static_cast<float>(times_sum) / ITERS;
    std::cerr << "Parallel average time: " << avg << std::endl;
    return avg;
}

int main() {
    parlay::sequence<parlay::sequence<size_t>> cube = gen_cube(SIZE);
    float avg_par = main_par(cube);
    float avg_seq = main_seq(cube);
    std::cerr << "Parallel average time is " << avg_seq / avg_par <<" times lower than sequential\n" << std::endl;
}
