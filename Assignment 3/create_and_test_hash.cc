// Adam Samulak
// Main file for Part I & II  A of Homework 3.
// TestFunctionForHashTable ( ) takes an input txt file as well as a
// test txt file.
//
// User provides both txt files and the type of the has table that should
// be used (quadratic, linear, double). When using the double table
// user can specify the R value, if R value is not provided it defaults
// to 89.

#include <fstream>
#include <iostream>
#include <string>
#include "linear_probing.h"
#include "double_hashing.h"
#include "quadratic_probing.h"

using namespace std;

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
			      									const string &words_filename,
			      									const string &query_filename) {
	// Part I & II
	// Construc the has table with the provided txt file
  hash_table.MakeEmpty();
	std::string words_line;
  std::ifstream words_file;
  words_file.open(words_filename);

  while(std::getline(words_file, words_line))
    hash_table.Insert(words_line);

  words_file.close();

	// Print out the output
  std::cout << "number_of_elements: " << hash_table.num_of_elements() << std::endl;
  std::cout << "size_of_table: " << hash_table.table_size() << std::endl;
  std::cout << "load_factor: " << hash_table.load_factor() << std::endl;
  std::cout << "average_collisions: " << hash_table.average_collisions() << std::endl;
  std::cout << "total_collisions: " <<  hash_table.num_of_collisions() << std::endl;
  std::cout << std::endl;

	// Open the test txt file and check the table for each word
	// from the test file.
  std::string query_line;
  std::ifstream query_file;
  query_file.open(query_filename);

	// Reset collisions
  hash_table.reset_collision_count();

	// Check for each word and print the desired output
  while(std::getline(query_file, query_line)){
  	if(hash_table.Contains(query_line)){
  		std::cout << query_line << " Found " << hash_table.num_of_collisions() + 1 << std::endl;
  		hash_table.reset_collision_count();
  	}else{
  		std::cout << query_line << " Not_Found " << hash_table.num_of_collisions() + 1 << std::endl;
  		hash_table.reset_collision_count();
  	}// End if
  }// End while
  query_file.close();
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5) {
		const string rvalue(argument_list[4]);
	  R = stoi(rvalue);
    }
    if (param_flag == "linear") {
       HashTableLinear<string> linear_probing_table;
       TestFunctionForHashTable(linear_probing_table, words_filename,
       			 query_filename);
    } else if (param_flag == "quadratic") {

	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename,
				query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
	HashTableDouble<string> double_probing_table;
	// Set the R value
	double_probing_table.set_R(R);
	TestFunctionForHashTable(double_probing_table, words_filename,
				 query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
