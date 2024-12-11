#pragma once

#include "../bfs.h"

parlay::sequence<parlay::sequence<size_t>> gen_cube(size_t size);

constexpr size_t cube_index(size_t const i, size_t const j, size_t const k, size_t const size) {
    return i * size * size + j * size + k;
}
