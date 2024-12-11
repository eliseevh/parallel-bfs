#pragma once

#include <parlay/sequence.h>

std::vector<size_t> bfs_seq(size_t start_idx, parlay::sequence<parlay::sequence<size_t>> const& neighbors);

std::vector<size_t> bfs_par(size_t start_idx, parlay::sequence<parlay::sequence<size_t>> const& neighbors);
