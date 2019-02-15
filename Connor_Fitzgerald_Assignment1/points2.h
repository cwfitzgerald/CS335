// Connor Fitzgerald
// 2018-02-14
// Points2 is a templated array like class that stores a list of pairs.
// Each pair has two values of the templated type.

#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

namespace teaching_project {
	// Points2 is a templated array like class that stores a list of pairs.
	// Each pair has two values of the templated type.
	// Supports any Object type that supports operator+= and being streamed to an ostream and from an istream
	//
	// Sample Usage
	// teaching_project::Points2<int> a;
	// a.ReadPoints2() // Reads points in format <size> <point1.x> <point1.y> ...
	// std::cout << a; // Includes newline
	// std::cout << a + a; // Double all of the contents.
	template <typename Object>
	class Points2 {
	  public:
		// Zero-parameter constructor.
		Points2() noexcept : sequence_(nullptr), size_(0){};

		// Copy-constructor.
		Points2(const Points2& rhs) :
		    sequence_(new std::array<Object, 2>[rhs.size_]),
		    size_(rhs.size_) {
			std::copy_n(rhs.sequence_, rhs.size_, sequence_);
		}

		// Standard generic copy-and-swap idiom
		Points2& operator=(const Points2& rhs) {
			using std::swap; // For ADL
			Points2 tmp = rhs;
			swap(*this, tmp);
			return *this;
		}

		// Move-constructor.
		Points2(Points2&& rhs) noexcept : sequence_{rhs.sequence_}, size_{rhs.size_} {
			rhs.sequence_ = nullptr;
			rhs.size_ = 0;
		}

		// Move-assignment.
		// Just use std::swap() for all variables.
		Points2& operator=(Points2&& rhs) noexcept {
			using std::swap; // For ADL

			swap(sequence_, rhs.sequence_);
			swap(size_, rhs.size_);

			return *this;
		}

		~Points2() noexcept {
			delete[] sequence_;
		}

		// One parameter constructor.
		Points2(const std::array<Object, 2>& item) :
		    sequence_{new std::array<Object, 2>[1]},
		    size_{1} {
			sequence_[0] = item;
		}

		// Read a chain from standard input.
		void ReadPoints2() {
			// Part of code included (without error checking).
			std::string input_line;
			std::getline(std::cin, input_line);
			std::stringstream input_stream(input_line);
			if (input_line.empty())
				return;
			// Read size of sequence (an integer).
			int size_of_sequence;
			input_stream >> size_of_sequence;

			// My code:

			// re-init memory to the proper size
			delete[] sequence_;
			sequence_ = new std::array<Object, 2>[size_of_sequence];
			size_ = size_of_sequence;

			// There are twice as many tokens as there are points.
			// Boolean allows you to flip flop between writing to the x or the y
			bool first = true;
			Object token;
			for (int i = 0; input_stream >> token; ++i) {
				int index = i / 2;
				if (first) {
					sequence_[index][0] = token;
				}
				else {
					sequence_[index][1] = token;
				}
				first = !first;
			}
		}

		size_t size() const noexcept {
			return size_;
		}

		// @location: an index to a location in the sequence.
		// @returns the point at @location.
		// const version.
		// abort() if out-of-range.
		const std::array<Object, 2>& operator[](size_t location) const {
			if (location >= size_) {
				std::abort();
			}

			return sequence_[location];
		}

		//  @c1: A sequence.
		//  @c2: A second sequence.
		//  @return their sum. If the sequences are not of the same size, append the
		//    result with the remaining part of the larger sequence.
		friend Points2 operator+(const Points2& c1, const Points2& c2) {
			// Make copy of larger one because I know I need all of the elements
			// Get reference to smaller one to avoid unnessiary copy

			// Immediately invoked lambda expression as I'm feeling fancy
			Points2 max = [&] {
				if (c1.size_ > c2.size_) {
					return c1;
				}
				else {
					return c2;
				}
			}();
			// Must be a IILE
			Points2 const& min = [&]() -> Points2 const& {
				if (c1.size_ > c2.size_) {
					return c2;
				}
				else {
					return c1;
				}
			}();

			// Binary std::transform
			std::transform(min.sequence_, min.sequence_ + min.size_, max.sequence_, max.sequence_,
			               [](std::array<Object, 2> const& in, std::array<Object, 2> const& out) {
				               std::array<Object, 2> ret(out);
				               ret[0] += in[0];
				               ret[1] += in[1];
				               return ret;
			               });

			return max;
		}

		// Overloading the << operator.
		friend std::ostream& operator<<(std::ostream& out, const Points2& some_points2) {
			// Special case 0 to avoid messy refactoring
			if (some_points2.size_ == 0) {
				out << "()";
			}
			// Loop will not run if size is 0
			for (std::size_t i = 0; i < some_points2.size_; ++i) {
				out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1]
				    << ") ";
			}
			// Newline needed
			out << '\n';
			return out;
		}

	  private:
		// Sequence of points.
		std::array<Object, 2>* sequence_;
		// Size of sequence.
		size_t size_;
	};

} // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
