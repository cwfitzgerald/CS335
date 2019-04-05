// Connor Fitzgerald

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <locale>
#include <climits>



template <typename HashTableType>
void TestFunctionForHashTable(HashTableType& hash_table, const string& words_filename, const string& query_filename) {
	cout << "TestFunctionForHashTables..." << endl;
	cout << "Words filename: " << words_filename << endl;
	cout << "Query filename: " << query_filename << endl;
	
	hash_table.MakeEmpty();

	std::ifstream words_file(words_filename);
	std::ifstream query_file(query_filename);

	std::string tmp;
	while(std::getline(words_file, tmp)) {
		hash_table.Insert(tmp);
	}

	cout << "Collisions: " << hash_table.Collisions() << endl;
	cout << "Number of items: " << hash_table.Size() << endl;
	cout << "Size of hash table: " << hash_table.TableSize() << endl;
	cout << "Load factor: " << hash_table.LoadFactor() << endl;
	cout << "Avg. number of collisions: " << hash_table.AverageCollisions() << endl;

	while (std::getline(query_file, tmp)) {
		hash_table.ClearProbes();
		if (hash_table.Contains(tmp)) {
			std::cout << tmp << " Found " << hash_table.Collisions() + 1 << "\n";
		}
		else {
			std::cout << tmp << " Not Found " << hash_table.Collisions() + 1 << "\n";
		}
	}
}

// Sample main for program create_and_test_hash
int main(int argc, char** argv) {
	if (argc != 4) {
		cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
		return 0;
	}

	const string words_filename(argv[1]);
	const string query_filename(argv[2]);
	const string param_flag(argv[3]);

	if (param_flag == "linear") {
		HashTableLinear<string> linear_probing_table;
		TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
	}
	else if (param_flag == "quadratic") {
		HashTable<string> quadratic_probing_table;
		TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
	}
	else if (param_flag == "double") {
		HashTableDouble<string> double_probing_table;
		TestFunctionForHashTable(double_probing_table, words_filename, query_filename);    
	}
	else {
		cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
	}
	return 0;
}
