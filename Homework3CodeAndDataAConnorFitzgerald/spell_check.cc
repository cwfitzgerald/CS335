// Connor Fitzgerald

#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

void lower(std::string& text) {
	for (auto& c : text) {
		c = std::tolower(c);
	}
}

std::string lower_copy(std::string text) {
	lower(text);
	return text;
}

void strip_text(std::string& text, const char* characters = "\t\n\v\f\r ");
void strip_text(std::string& text, const char* characters) {
	if (text.empty()) {
		return;
	}

	auto first_char = text.find_first_not_of(characters);
	auto last_char = text.find_last_not_of(characters);

	// These will only both happen, or neither will happen
	if (first_char == std::string::npos && last_char == std::string::npos) {
		text = "";
		return;
	}

	std::size_t i = 0;
	text.erase(std::remove_if(text.begin(), text.end(),
		[&i, &first_char, &last_char](char) {
		auto const in_range = first_char <= i && i <= last_char;
		++i;
		return !in_range;
	}),
		text.end());
}

// Sample main for program spell_check
int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
		return 0;
	}

	const string document_filename(argv[1]);
	const string dictionary_filename(argv[2]);

	cout << "Input document filename is " << document_filename << endl;
	cout << "Input dictionary filename is " << dictionary_filename << endl;

	std::ifstream document(document_filename);
	std::ifstream dictionary_file(dictionary_filename);

	HashTable<std::string> dictionary;
	std::string tmp;
	while (std::getline(dictionary_file, tmp)) {
		dictionary.Insert(tmp);
	}

	std::string word;
	while (std::getline(document, word, ' ')) {
		strip_text(word);
		std::string word_stripped;
		std::copy_if(std::begin(word), std::end(word), std::back_inserter(word_stripped), [](char c) { return c != '\''; });
		word = lower_copy(word_stripped);
		if (word.size() == 0) {
			continue;
		}
		if(dictionary.Contains(word)) {
			continue;
		}
		std::string word2;
		for (auto i = word.begin(); i != word.end(); ++i) {
			word2 = std::string(word.begin(), i) + std::string(i + 1, word.end());
			if (dictionary.Contains(word2)) {
				std::cout << word << " -> " << word2 << '\n';
			}
		}
		for (auto i = word.begin(); i != word.end(); ++i) {
			for (char c = 'a'; c <= 'z'; ++c) {
				word2 = std::string(word.begin(), i) + c + std::string(i, word.end());
				if (dictionary.Contains(word2)) {
					std::cout << word << " -> " << word2 << '\n';
				}
			}
		}

		for (auto i = word.begin(); i != word.end() - 1; ++i) {
			word2 = word; // use as tmp
			swap(*i, *(i + 1));
			if (dictionary.Contains(word)) {
				std::cout << word << " -> " << word2 << '\n';
			}
			word = word2;
		}
	}

	return 0;
}
