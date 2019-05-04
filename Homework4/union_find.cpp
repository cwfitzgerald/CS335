#include "union_find.hpp"
#include <cassert>
#include <iterator>

void UnionFind::add_node(std::size_t value) {
	if(!find(value)) {
		data_.push_back({ value });
	}
}

bool UnionFind::find(std::size_t value) {
	return find_impl(value) != data_.end();
}

void UnionFind::join(std::size_t first, std::size_t second) {
	auto first_itr = find_impl(first);
	auto second_itr = find_impl(second);

	assert(first_itr != data_.end());
	assert(second_itr != data_.end());

	if(first_itr != second_itr) {
		std::copy(second_itr->begin(), second_itr->end(), std::inserter(*first_itr, first_itr->end()));
		data_.erase(second_itr);
	}
}

std::size_t UnionFind::count() const {
	return data_.size();
}

decltype(UnionFind::data_)::iterator UnionFind::find_impl(std::size_t value) {
	for (auto i = data_.begin(); i != data_.end(); ++i) {
		auto& set = *i;
		auto iter = set.find(value);
		bool found = iter != set.end();
		if (found) {
			return i;
		}
	}
	return data_.end();
}


