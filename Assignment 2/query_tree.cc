// Adam Samulak
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.
//
// QueryTree( ) takes an input file with recognition sequences and their enzymes
// and creates a desired tree (BST or AVL)
// 
// Then it prompts the user for 3 recognition sequences and searches the tree for them
// it then returns the results
#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace {


	// @db_filename: an input filename.
	// @a_tree: an input tree of the type TreeType. It is assumed to be
	//  empty.
	template <typename TreeType>
	void QueryTree(const string &db_filename, TreeType &a_tree) {
		// Code for running Part2(a)
		// Parse input file @db_filename and fill tree @a_tree
		// Then prompt the user for exactly three strings (do a loop) and
		// provide the results of find() as described in the assignment.
		std::string db_line;
		std::ifstream somefile(db_filename.c_str());
		std::string delimiter = "/";
		std::string str;

		// Skip first 10 lines
		for(size_t i = 0; i < 10; i++){
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
			while((pos = db_line.find(delimiter)) != std::string::npos){
				str = db_line.substr(0, pos);
					// Skip the empty string at the end of each line
					if(str != ""){
						// Add the new SequenceMap to the tree
						a_reco_seq = str;
						SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
						a_tree.insert(new_sequence_map);
					} // End if
				db_line.erase(0, pos + delimiter.length());
			}// End second while.
		} // End first while.


		vector<SequenceMap> in;
	
		// Prompts user for 3 recogniton sequences
		for( size_t j = 0; j < 3; j++){
  			string s;
  			string empty = "";
  			cin >> s;
  			in.push_back(SequenceMap(s, ""));
		}
  
		// Prints the coresponding enzymes or Not Found
		for(size_t i = 0; i < in.size(); i++){
			a_tree.find(in[i]);
		}
	}// End QueryTree

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;

  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
    //a_tree.printTree();
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
    //a_tree.printTree();
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
