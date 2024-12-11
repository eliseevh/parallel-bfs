#include "utils.h"

constexpr std::pair<size_t, size_t> bounds(size_t const i, size_t const size) {
    return std::make_pair(i > 0 ? i - 1 : i, i < size - 1 ? i + 1 : i);
}

parlay::sequence<parlay::sequence<size_t>> gen_cube(size_t const size) {
    parlay::sequence<parlay::sequence<size_t>> cube(size * size * size);
    for (size_t ci = 0; ci < size; ci++) {
        for (size_t cj = 0; cj < size; cj++) {
            for (size_t ck = 0; ck < size; ck++) {
                size_t c_idx = cube_index(ci, cj, ck, size);
                auto [ilb, igb] = bounds(ci, size);
                auto [jlb, jgb] = bounds(cj, size);
                auto [klb, kgb] = bounds(ck, size);
                for (size_t i = ilb; i <= igb; i++) {
                    if (i != ci) {
                        cube[c_idx].push_back(cube_index(i, cj, ck, size));
                    }
                }
                for (size_t j = jlb; j <= jgb; j++) {
                    if (j != cj) {
                        cube[c_idx].push_back(cube_index(ci, j, ck, size));
                    }
                }
                for (size_t k = klb; k <= kgb; k++) {
                    if (k != ck) {
                        cube[c_idx].push_back(cube_index(ci, cj, k, size));
                    }
                }
            }
        }
    }
    return cube;
}
