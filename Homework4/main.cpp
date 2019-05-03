#include "adjacency_graph.hpp"
#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>

std::vector<dd_pair> parse_queries(std::istream& f) {
    std::vector<dd_pair> list;
    std::size_t idx1, idx2;
    while(f >> idx1 >> idx2) {
        list.emplace_back(dd_pair{idx1, idx2});
    }
    return list;
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        std::cout << "Not enough args\n";
        return 1;
    }

    std::ifstream graph_file(argv[1]);

    assert(graph_file);

    AdjacencyGraph graph = AdjacencyGraph::parse_from_stream(graph_file);

    std::ifstream q_file(argv[2]);

    assert(q_file);

    auto queries = parse_queries(q_file);

    for (auto& q : queries) {
        auto const&& adjacents = graph.adjacents(q.first);
        auto itr = std::find_if(adjacents.begin(), adjacents.end(), [&](Adj val) {
            return val.end == q.second;
        });
        if (itr != adjacents.end()) {
            std::cout << q.first << ' ' << q.second << ": Connected, weight of edge is " << itr->weight << '\n';
        }
        else {
            std::cout << q.first << ' ' << q.second << ": Not connected\n";
        }
    }
}
