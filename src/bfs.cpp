#include "bfs.h"

#include <parlay/primitives.h>

std::vector<size_t> bfs_seq(size_t const start_idx, parlay::sequence<parlay::sequence<size_t>> const& neighbors) {
    std::vector<size_t> result(neighbors.size(), 0);
    std::vector visited(neighbors.size(), false);
    visited[start_idx] = true;
    std::queue<size_t> q;
    q.push(start_idx);
    while (!q.empty()) {
        size_t u = q.front();
        q.pop();
        for (size_t v : neighbors[u]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
                result[v] = result[u] + 1;
            }
        }
    }
    return result;
}

std::vector<size_t> bfs_par(size_t const start_idx, parlay::sequence<parlay::sequence<size_t>> const& neighbors) {
    std::vector<size_t> result(neighbors.size(), 0);

    parlay::sequence<std::atomic_bool> visited(neighbors.size());

    visited[start_idx] = true;
    parlay::sequence frontier(1, start_idx);
    size_t dist = 0;
    while (!frontier.empty()) {
        frontier = filter(flatten(map(frontier, [&] (size_t const u) {
            // Use cut to create slice to prevent sequence copying (slice creation and copying is O(1))
            return neighbors[u].cut(0, neighbors[u].size());
        })), [&] (size_t const v) {
            bool value = false;
            return visited[v].compare_exchange_strong(value, true);
        });
        ++dist;
        parlay::parallel_for(0, frontier.size(), [&] (size_t const u) {
            result[frontier[u]] = dist;
        });
    }

    return result;
}
