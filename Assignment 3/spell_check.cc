// Adam Samulak
// spell_check.cc: A simple spell checker.
// The spell_check.cc reads in the words to build a dictionary by using a double_hashing
// class. Then a sample text is processed by removing punctuations and setting
// it to lower case characters.
//
// Individual words are checked for in the dictionary. Later each word is modified
// as described in the assignment. Again dictionary is checked for the new word.

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "double_hashing.h"
using namespace std;

// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;

  // Fill dictionary_hash.
  std::string dict_line;
  std::ifstream dict_file;
  dict_file.open(dictionary_file);

  while(dict_file >> dict_line)
      dictionary_hash.Insert(dict_line);

  dict_file.close();

  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file) {

  // Read in txt file line by line and split it into words
  std::fstream doc_file;
  std::string doc_line;
  std::string doc_word;
  doc_file.open(document_file);

  while(std::getline(doc_file, doc_line)){
    std::stringstream ss_line(doc_line);
    while (ss_line >> doc_word){
      // Set all characters to lower case and
      // remove punctuations (, and .)
      for (size_t i = 0; i < doc_word.length(); i++){
        doc_word[i] = tolower(doc_word[i]);
        if (doc_word[i] == ',' || doc_word[i] == '.'){
          doc_word.erase(i);
        }
      }
      // Check the dictionary for a given word
      // and check the tree cases listed in the assignment
      // if the word is not found.
      if (dictionary.Contains(doc_word))
        std::cout << doc_word << " is CORRECT" << std::endl;
      else{
        std::cout << doc_word << " is INCORRECT" << std::endl;
        std::string tmp_word = doc_word;

        // Part 3 a:
        // Change individual character in the word and check the dictionary
        for (size_t i = 0; i < doc_word.length() + 1; i++) {
          for (char character = 97; character <= 122; character++) {
            tmp_word.insert(i, 1, character);
            if (dictionary.Contains(tmp_word))
              std::cout << "*** " << doc_word << " -> " << tmp_word << " *** case A" <<  std::endl;
            tmp_word = doc_word;
          }// End nested for loop
        }// End first for loop

        tmp_word = doc_word;
        // Part 3 b:
        // Deleting individual character in the word and check the dictionary
        for (size_t i = 0; i < doc_word.length(); i++) {
          tmp_word.erase(i, 1);
          if (dictionary.Contains(tmp_word))
            std::cout << "*** " << doc_word << " -> " << tmp_word << " *** case B" <<  std::endl;
          tmp_word = doc_word;
        }// End for loop

        tmp_word = doc_word;
        // Part 3 c:
        // Swaping adjacent characters in the word
        for (size_t j = 0; j < doc_word.length(); j++) {
          swap(tmp_word[j], tmp_word[j + 1]);
          if (dictionary.Contains(tmp_word))
            std::cout << "*** " << doc_word << " -> " << tmp_word << " *** case C" <<  std::endl;
          tmp_word = doc_word;
        }// End for loop

      }// End else
    }// End get word while
  }// End get line while
  doc_file.close();
}
// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }

  testSpellingWrapper(argc, argv);

  return 0;
}
