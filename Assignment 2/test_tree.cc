// Adam Samulak
// Main file for Part2(b) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.
//
// TestTree( ) takes two imput files. Database file that is used to create a tree
// and a sequence file that is used to check for recognition sequences and is also used
// to remove sequences from the tree. Through out the program each tree is examined for certain
// parameters like # of nodes, average depth, etc.


#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <math.h> 
using namespace std;

namespace {

	// @db_filename: an input database filename.
	// @seq_filename: an input sequences filename.
	// @a_tree: an input tree of the type TreeType. It is assumed to be
	//  empty.
	template <typename TreeType>
	void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
		// Code for running Part2(a)
		// Parse input file @db_filename and fill tree @a_tree
		std::string db_line;
		std::ifstream somefile(db_filename.c_str());
		std::string delimiter = "/";
		std::string str;

		// Skip first 10 lines
		for (size_t i = 0; i < 10; i++) {
			std::getline(somefile, db_line);
		}

		// Read the file line-by-line and uses delimiter to move to the next string in line
		while (std::getline(somefile, db_line)) {
			// Find position of the first delimiter "/"
			size_t pos = 0;
			pos = db_line.find(delimiter);
			str = db_line.substr(0, pos);
			// Assign the enzyme acronym and move to the recognition sequence
			string an_enz_acro = str;
			string a_reco_seq;
			db_line.erase(0, pos + delimiter.length());

			// Finds consecutive recognition sequences
			while ((pos = db_line.find(delimiter)) != std::string::npos) {
				str = db_line.substr(0, pos);
				// Skip the empty string at the end of each line
				if (str != "") {
					// Add the new SequenceMap to the tree
					a_reco_seq = str;
					SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
					a_tree.insert(new_sequence_map);
				} // End if
				db_line.erase(0, pos + delimiter.length());
			}// End second while.
		} // End first while.
  
  
		// Part 2 print number of nodes
		cout << "2: " << a_tree.node_number() << endl;

		// Part 3
		// Print average depth of the tree
		cout << "3a: " <<a_tree.average_tree_depth() << endl;
		// Print the ratio of the average depth to log!
		cout << "3b: " <<a_tree.average_tree_depth()/log2(a_tree.node_number()) << endl;

		// Part 4
		// Use the sequence file to search the tree for recognition sequences
		std::ifstream seq_file(seq_filename.c_str());
		std::string seq_line;
		int counter = 0;
		// Check each sequence
		// counter keeps track of each recurssive call
		while(std::getline(seq_file, seq_line)){
			a_tree.contains(SequenceMap(seq_line, ""), counter);
		}
		// Print sucessful queries
		cout << "4a: " <<a_tree.queries_number() << endl;
		// Prints the average number of recursion calls 
		cout << "4b: " <<float(counter)/float(a_tree.queries_number()) << endl;

		// Reset querie variable for the next part
		a_tree.reset_queries_num();
  
		// Read the file again and delete every other string
		// keep track of each recursive call
		std::ifstream seq_file_repeat(seq_filename.c_str());
		std::string seq_line_repeat;
		int count = 0;
		int total_calls = 0;
		int removes = 0;
		while(std::getline(seq_file_repeat, seq_line_repeat)){
  			if( count%2 == 0){
				SequenceMap sequence(seq_line_repeat, "");
  				if(a_tree.contains(sequence, total_calls))
					a_tree.remove(sequence, removes);
  			}
  		count++;
		}

		// Part 5
		// Print sucessfull removes
		cout << "5a: " <<a_tree.queries_number() << endl;
		// Print average number of recursion calls
		cout << "5b: " <<float(removes)/float(a_tree.queries_number()) << endl;

		//Part 6
		// Print the number of nodes
		cout << "6a: " <<a_tree.node_number() << endl;
		// Print average depth of the tree
		cout << "6b: " <<a_tree.average_tree_depth() << endl;
		// Print the ratio of the average depth to log!
		cout << "6c: " <<a_tree.average_tree_depth()/log2(a_tree.node_number()) << endl;
	}// End of TestTree

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);

  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);

  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
