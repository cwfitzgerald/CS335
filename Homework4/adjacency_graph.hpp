#pragma once

#include <iosfwd>
#include <vector>
#include <limits>
#include <unordered_map>

using ss_pair = std::pair<std::size_t, std::size_t>;

struct Adj {
    std::size_t start;
    std::size_t end;
    float weight;
};

struct Node {
	float distance{std::numeric_limits<float>::infinity()};
	std::size_t prev{ std::numeric_limits<std::size_t>::max() };
	bool visited{ false };
};

class AdjacencyGraph {
public:
	void add_edge(std::size_t start, std::size_t end, float weight);
	void remove_edge(std::size_t start, std::size_t end);

	std::vector<Adj> adjacents(std::size_t idx);

	Node& get_node(std::size_t idx);
    void create_node(std::size_t idx);

    static AdjacencyGraph parse_from_stream(std::istream& file);

	std::size_t node_count() const noexcept {
		return nodes.size();
	}

private:
	std::vector<Adj> adjacency;
	std::unordered_map<std::size_t, Node> nodes;
};
