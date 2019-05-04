#pragma once
#include <set>
#include <vector>

class UnionFind {
public:
	void add_node(std::size_t value);

	bool find(std::size_t value);

	void join(std::size_t first, std::size_t second);

	std::size_t count() const;

private:
	std::vector<std::set<std::size_t>> data_;

	decltype(data_)::iterator find_impl(std::size_t value);
};
