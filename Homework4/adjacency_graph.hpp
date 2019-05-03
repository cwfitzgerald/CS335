#pragma once

#include <iosfwd>
#include <vector>
#include <unordered_map>

using dd_pair = std::pair<std::size_t, std::size_t>;

struct Adj {
    std::size_t start;
    std::size_t end;
    float weight;
};

class Node {

};

class AdjacencyGraph {
public:
	void add_edge(std::size_t start, std::size_t end, float weight);
	void remove_edge(std::size_t start, std::size_t end);

	std::vector<Adj> adjacents(std::size_t idx);


	Node get_node(std::size_t idx);
    void create_node(std::size_t idx);

    static AdjacencyGraph parse_from_stream(std::istream& file);

private:
	std::vector<Adj> adjacency;
	std::unordered_map<std::size_t, Node> nodes;
};
