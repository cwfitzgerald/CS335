#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <numeric>

struct matrix {
	int left;
	int right;
};

struct slice {
	int start;
	int size; // inclusive because I'm a idiot and can't index to save my life

	friend bool operator==(slice const& lhs, slice const& rhs) {
		return lhs.start == rhs.start
			&& lhs.size == rhs.size;
	}

	friend bool operator!=(slice const& lhs, slice const& rhs) {
		return !(lhs == rhs);
	}
};

// custom specialization of std::hash can be injected in namespace std
namespace std {
	template<>
	struct hash<slice> {
		using argument_type = slice;
		using result_type = std::size_t;
		result_type operator()(argument_type const& s) const noexcept {
			return std::hash<std::size_t>{}(*reinterpret_cast<std::size_t const*>(&s));
		}
	};
}

std::size_t cost(std::vector<matrix>& mats, slice s);

std::size_t memoize_cost(std::vector<matrix>& mats, slice s) {
	static std::unordered_map<slice, std::size_t> memo;
	auto itr = memo.find(s);
	if (itr != memo.end()) {
		return itr->second;
	}
	return memo.insert(std::make_pair(s, cost(mats, s))).first->second;
}

std::size_t cost(std::vector<matrix>& mats, slice const s) {
	if (s.size == 1) {
		return 0;
	}
	std::size_t min_cost = std::numeric_limits<std::size_t>::max();
	for (int i = 1; i < s.size; ++i) {
		slice slice_a{ s.start, i };
		slice slice_b{ s.start + i, s.size - i };
		std::size_t cost_a = memoize_cost(mats, slice_a);
		std::size_t cost_b = memoize_cost(mats, slice_b);
		std::size_t start_dim = mats[slice_a.start].left;
		std::size_t mid_dim = mats[slice_b.start].left;
		std::size_t end_dim = mats[s.start + s.size - 1].right;

		std::size_t cost = cost_a + cost_b + (start_dim * mid_dim * end_dim);
		min_cost = std::min(min_cost, cost);
	}
	return min_cost;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Not enough arguments.\n";
		return 1;
	}

	std::ifstream f(argv[1]);

	assert(f);

	std::vector<int> sizes;
	int size;
	while(f >> size) {
		sizes.emplace_back(size);
	}
	std::vector<matrix> mats;
	std::transform(sizes.begin() + 1, sizes.end(), sizes.begin(), std::back_inserter(mats), [](int r, int l) {
		return matrix{ l, r };
	});

	std::cout << cost(mats, slice{ 0, int(mats.size()) }) << '\n';
}
