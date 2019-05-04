#include <cassert>
#include "adjacency_graph.hpp"
#include <limits>
#include <sstream>
#include <algorithm>

void AdjacencyGraph::add_edge(std::size_t const start, std::size_t const end, float const weight) {
    create_node(start);
    create_node(end);

    Adj adj{start, end, weight};

    auto itr = std::upper_bound(adjacency.begin(), adjacency.end(), adj, [&](Adj left, Adj right) {
        return ss_pair(left.start, left.end) < ss_pair(right.start, right.end);
    });
    adjacency.insert(itr, adj);
}

void AdjacencyGraph::remove_edge(std::size_t start, std::size_t end) {
    ss_pair pair(start, end);

    auto itr = std::lower_bound(adjacency.begin(), adjacency.end(), pair, [&](Adj left, ss_pair right) {
        return ss_pair(left.start, left.end) < right;
    });
    assert(itr != adjacency.end());
    adjacency.erase(itr - 1);
}

std::vector<Adj> AdjacencyGraph::adjacents(std::size_t const idx) {
    auto const lower = std::lower_bound(adjacency.begin(), adjacency.end(), idx, [](Adj const& lhs, std::size_t rhs) {
        return lhs.start < rhs;
    });
    auto const upper = std::upper_bound(adjacency.begin(), adjacency.end(), idx, [](std::size_t lhs, Adj const& rhs) {
        return lhs < rhs.start;
    });

    return std::vector<Adj>(lower, upper);
}

Node& AdjacencyGraph::get_node(std::size_t idx) {
    auto itr = nodes.find(idx);
    assert(itr != nodes.end());
    return itr->second;
}

void AdjacencyGraph::create_node(std::size_t idx) {
    if(nodes.find(idx) == nodes.end()) {
        nodes[idx];
    }
}

// Add some sanity checking b/c iostreams are god awful
#define IOS_ASSERT(op) assert(bool(op))

AdjacencyGraph AdjacencyGraph::parse_from_stream(std::istream& file) {
    AdjacencyGraph ag;

    std::size_t count;
    IOS_ASSERT(file >> count);
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string tmp;
    while (std::getline(file, tmp)) {
        std::istringstream line_stream(tmp);

        std::size_t start;
        IOS_ASSERT(line_stream >> start);

        std::size_t end;
        float weight;
        while(line_stream >> end >> weight) {
            ag.add_edge(start, end, weight);
        }
    }
    return ag;
}
