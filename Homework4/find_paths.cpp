#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <queue>
#include "adjacency_graph.hpp"

// Distance/index
using fs_pair = std::pair<float, std::size_t>;

std::vector<std::size_t> dijkstra(AdjacencyGraph& graph, std::size_t start_idx, std::size_t const end_idx) {
	// Less-first priority queue (inverted by std::greater over std::less)
	// Exploits lexicographical ordering of pairs to always give the minimum first
	std::priority_queue<fs_pair, std::vector<fs_pair>, std::greater<>> pq;

	// Clear nodes
	for (std::size_t i = 1; i <= graph.node_count(); ++i) {
		graph.get_node(i) = Node{};
	}

	// Get some useful references
	Node& start = graph.get_node(start_idx);
	Node& end = graph.get_node(end_idx);

	// Mark out starting point
	start.distance = 0.f;
	start.visited = true;

	// Add our starting node to our search	
	pq.emplace<fs_pair>({ 0.f, start_idx });

	// We aren't done yet
	while (!pq.empty() && !end.visited) {
		// Our current working node is the node with the least distance.
		std::size_t const current_idx = pq.top().second;
		Node& current = graph.get_node(current_idx);
		// Remove that node
		pq.pop();

		// Mark it touched
		current.visited = true;

		// Iterate through edges
		for (auto& child : graph.adjacents(current_idx)) {
			// Reference to the destination of the edge
			std::size_t next_idx = child.end;
			Node& next = graph.get_node(next_idx);

			// We already went here, no need to come back
			if(next.visited) {
				continue;
			}

			// Alias
			float const weight = child.weight;

			// Our distance is actually shorter, update it
			if(next.distance > current.distance + weight) {
				next.distance = current.distance + weight;
				next.prev = current_idx;
				// Add that node to the list of places to look again
				pq.emplace<fs_pair>({ next.distance, next_idx });
			}
		}
	}
	// Assemble the path by walking backwards
	std::vector<std::size_t> path;

	// std::numeric_limits<std::size_t>::max() is a value representing no-previous
	std::size_t idx = end_idx;
	while (idx != std::numeric_limits<std::size_t>::max()) {
		path.push_back(idx);
		idx = graph.get_node(idx).prev;
	}
	// Reverse the path back to normal
	std::reverse(path.begin(), path.end());
	return path;
}

int main(int const argc, char ** argv) {
	if (argc < 3) {
		std::cout << "Not enough args\n";
		return 1;
	}

	// Load graph
	std::ifstream graph_file(argv[1]);

	// Ensure we loaded it
	assert(graph_file);

	// Parse it down
	AdjacencyGraph graph = AdjacencyGraph::parse_from_stream(graph_file);

	// Parse the starting index
	char* end;
	std::size_t start = std::strtol(argv[2], &end, 10);
	assert(end != argv[2]);

	// Find all destinations and print
	for (std::size_t i = 1; i <= graph.node_count(); i++) {
		auto result = dijkstra(graph, start, i);
		std::cout << i << ": ";
		for (auto& idx : result) {
			std::cout << idx << ", ";
		}
		std::cout << "Cost: " << graph.get_node(i).distance << ".\n";
	}
}
