#include "adjacency_graph.hpp"
#include "union_find.hpp"
#include <iostream>
#include <random>
#include <cassert>

int main(int const argc, char ** argv) {
	if (argc < 2) {
		std::cout << "Not enough args\n";
		return 1;
	}

	// Parse the count
	char* strtol_end;
	std::size_t const count = std::strtol(argv[1], &strtol_end, 10);
	assert(strtol_end != argv[1]);

	UnionFind uf;
	for (std::size_t i = 1; i <= count; ++i) {
		uf.add_node(i);
	}

	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<std::size_t> dist(1, count);

	AdjacencyGraph ag;
	while (uf.count() != 1) {
		std::size_t start = dist(mt);
		std::size_t end = dist(mt);

		if (start == end) {
			continue;
		}

		ag.add_edge(start, end, 1);
		ag.add_edge(end, start, 1);

		uf.join(start, end);
	}

	std::cout << "              Edges: " << ag.edge_count() << '\n';
	std::size_t sum = 0;
	std::size_t min = std::numeric_limits<std::size_t>::max();
	std::size_t max = 0;
	for (std::size_t i = 1; i <= count; ++i) {
		std::size_t val = ag.adjacents(i).size();
		min = std::min(val, min);
		max = std::max(val, max);
		sum += val;
	}
	float average = static_cast<float>(sum) / ag.node_count();

	std::cout << "Smallest Out Degree: " << min << " edges\n";
	std::cout << " Largest Out Degree: " << max << " edges\n";
	std::cout << " Average Out Degree: " << average << " edges\n";
}
