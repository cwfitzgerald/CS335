#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include "prime.h"


// Quadratic probing implementation.
template <typename HashedObj>
class HashTableDouble {
	public:
	enum EntryType { ACTIVE, EMPTY, DELETED };

	explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size)) {
		MakeEmpty();
	}

	bool Contains(const HashedObj& x) const {
		return IsActive(FindPos(x));
	}

	void MakeEmpty() {
		current_size_ = 0;
		for (auto& entry : array_)
			entry.info_ = EMPTY;
	}

	bool Insert(const HashedObj& x) {
		// Insert x as active
		size_t current_pos = FindPos(x);
		if (IsActive(current_pos))
			return false;

		array_[current_pos].element_ = x;
		array_[current_pos].info_ = ACTIVE;

		// Rehash; see Section 5.5
		if (++current_size_ > array_.size() / 2)
			Rehash();
		return true;
	}

	bool Insert(HashedObj&& x) {
		// Insert x as active
		size_t current_pos = FindPos(x);
		if (IsActive(current_pos))
			return false;

		array_[current_pos] = std::move(x);
		array_[current_pos].info_ = ACTIVE;

		// Rehash; see Section 5.5
		if (++current_size_ > array_.size() / 2)
			Rehash();

		return true;
	}

	bool Remove(const HashedObj& x) {
		size_t current_pos = FindPos(x);
		if (!IsActive(current_pos))
			return false;

		array_[current_pos].info_ = DELETED;
		return true;
	}

	size_t Size() const {
		return current_size_;
	}

	size_t TableSize() const {
		return array_.size();
	}

	float LoadFactor() const {
		return float(current_size_) / float(array_.size());
	}

	size_t Collisions() const {
		return collisions_;
	}

	float AverageCollisions() const {
		return float(collisions_) / float(current_size_);
	}

	void ClearProbes() const {
		collisions_ = 0;
	}

	private:
	struct HashEntry {
		HashedObj element_;
		EntryType info_;

		HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
			: element_{e}, info_{i} { }

		HashEntry(HashedObj&& e, EntryType i = EMPTY)
			: element_{std::move(e)}, info_{i} {}
	};


	std::vector<HashEntry> array_;
	size_t current_size_;
	mutable size_t collisions_ = 0;

	bool IsActive(size_t current_pos) const {
		return array_[current_pos].info_ == ACTIVE;
	}

	size_t FindPos(const HashedObj& x) const {
		size_t current_pos = InternalHash(x);
		size_t const offset = InternalRehash(x);

		while (array_[current_pos].info_ != EMPTY &&
			array_[current_pos].element_ != x) {
			collisions_ += 1;
			current_pos += offset;
			if (current_pos >= array_.size())
				current_pos -= array_.size();
		}
		return current_pos;
	}

	void Rehash() {
		std::vector<HashEntry> old_array = array_;

		// Create new double-sized, empty table.
		array_.resize(NextPrime(2 * old_array.size()));
		for (auto& entry : array_)
			entry.info_ = EMPTY;

		// Copy table over.
		current_size_ = 0;
		for (auto& entry : old_array)
			if (entry.info_ == ACTIVE)
				Insert(std::move(entry.element_));
	}

	size_t InternalHash(const HashedObj& x) const {
		static std::hash<HashedObj> hf;
		return hf(x) % array_.size();
	}

	size_t InternalRehash(const HashedObj& x) const {
		static std::hash<HashedObj> hf;
		return (89 - (hf(x)) % 89) % array_.size();
	}
};
