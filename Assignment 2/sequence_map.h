// Adam Samulak
//** Sequence Map Class **//
// It contains a recognition sequence Ex. CTGNNAATG and all the enzyme names that work for that sequence
// This class provides < and << overloads and a Merge function that adds an enzyme to a recognition sequence

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class SequenceMap {

// Objec contains the "Big Five"
//
// Two parameter costructor assigns recognition sequence and the name of the enzyme
//
// < operator compares two stings to determine their order in a tree
// 
// << prints out enzyme acronyms
//
// Merge adds the enzye acronyme from one SequenceMap to another.

public:

    // Zero-parameter constructor.
    SequenceMap() = default;

    // Copy-constructor.
    SequenceMap(const SequenceMap& rhs) = default;

    // Move-constructor. 
    SequenceMap(SequenceMap&& rhs) = default;
    
    // Copy-assignment.
    SequenceMap& operator=(const SequenceMap &rhs) = default;
    
    // Move-assignment.
    SequenceMap& operator=(SequenceMap &&rhs) = default;
    
    // Deconstructor.
    ~SequenceMap() = default;

    // Two parameter constructor wit two strings
    SequenceMap(const string& a_rec_seq, const string& an_enz_acro) {
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    // < overload
    // compares two recognition sequences to provide order in a tree
    bool operator<(const SequenceMap& rhs) const{
        if(recognition_sequence_ < rhs.recognition_sequence_)
        	return true;
        else
       	return false;
    }

    // << overload
    // prints all the enzymes associated with the recognition sequence
    friend std::ostream& operator<<(std::ostream& out,  const SequenceMap& rhs) {
       for(size_t enz = 0; enz < rhs.enzyme_acronyms_.size(); ++enz){		
            out << rhs.enzyme_acronyms_[enz];
        }
        out << endl;
        return out;
    }

    // Function assumes that recognition sequence is the same in both objects
    // and it merges the other_sequence's ezyme acronym with current object.
    void Merge(const SequenceMap& other_sequence) {
        for(size_t i =0; i < other_sequence.enzyme_acronyms_.size(); i++){
        	enzyme_acronyms_.push_back(" " + other_sequence.enzyme_acronyms_[i]);
        }
    }
private:
	string recognition_sequence_;
	vector<string> enzyme_acronyms_;
};
#endif
