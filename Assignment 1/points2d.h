// Adam Samulak
//** Points2D Class **//
// Individual points (1, 2) are stored in a 2-dimensional array x- & y-coordinates respectiverly.
// This class allows for printing out points from the object, 
// addition of point by point regardless of the size of the two objects.

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project{

// Object cotains the "big five".
// 
// Additionally, a single parameter constructor exists for creating a object
// with a single point:
// Ex. const array<int, 2> a_point2{{1, 2}} 
//
// Standard input can be used to create an object (obj.ReadPoints2D()).
// User needs to probvide an integer that provides # of points
// and values for these points:
// Ex. 2 1 1 3 3 -> (1, 1) (2, 2)
//
// obj.size() returns the number of points in the object
// Ex. a_point2.size() --> 1
// 
// + $ << operators are overriten:
// 
// + operator adds two objects by its coresponding point.
// If two of the objects are of different size all, all points are 
// added together and the points that are only in one array are kept the same:
// Ex. Points2D<int> a{{1, 1}, {4, 4}}
//     Points2D<int> b{{2, 2}}
//     Points2D<int> c = a + b
//     c is {(3, 3) (4, 4)}
// << operator prints all the points from a given object:
// Ex. cout << c;
//     (3, 3) (4, 4)

template<typename Object>
class Points2D{
 public:
  // Default "big five"

  // Zero-parameter constructor. 
  Points2D(){
  	size_ = 0;
  	sequence_ = nullptr;
  };

  // Copy-constructor.
  Points2D(const Points2D &rhs){
    // Initialize variables & copy coordinates of each point
  	size_ = rhs.size();
  	sequence_ = new std::array<Object,2>[rhs.size()];
  	for(size_t i = 0; i < rhs.size(); i++){
  		sequence_[i] = rhs.sequence_[i];
  	}
  };
    
  // Move-constructor. 
  Points2D(Points2D &&rhs){
      // Move rhs variables and set them to zero and nullptr
      size_ = rhs.size();
      rhs.size_ = 0;
      sequence_ = std::move(rhs.sequence_);
      rhs.sequence_ = nullptr;
  };

  // Copy-assignment. 
  Points2D& operator=(const Points2D &rhs){
      Points2D copy = rhs; 
      std::swap(*this, copy);
      return *this;
  };

  // Move-assignment.
  Points2D& operator=(Points2D &&rhs){
      // Swap rhs and the variables of the new object
      std::swap(size_, rhs.size_);
      std::swap(sequence_, rhs.sequence_);
      return *this;
  };
  // Destructor.
  ~Points2D(){
  	delete[] sequence_;
  };

  // End of big-five.

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item){
    // Use the array to create a one poin object
  	size_ = 1;
  	sequence_ = new std::array<Object, 2>{item};
  }

  // Read a chain from standard input.
  void ReadPoints2D() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    size_ = size_of_sequence;
    sequence_ = new std::array<Object, 2>[size_of_sequence];
    Object token;
    for (int i = 0; input_stream >> token; ++i) {
      // Read coordinates.
      sequence_[i][0] = token; 
      input_stream >> token; 
      sequence_[i][1] = token; 
    }
    std::cout << std::endl;
  }

  // @return the number of points in the object
  size_t size() const{
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const{ 
      if (location == size_){
      	abort(); 
      }
      return sequence_[location];
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2D operator+(const Points2D &c1, const Points2D &c2){
	 // If c1 >= c2 use a copy constructor to make a copy of c1 and add c2 to it
     if(c1.size() >= c2.size()){
		Points2D out = c1;
	 	for(size_t j = 0; j < c2.size(); ++j){
			out.sequence_[j][0] = out.sequence_[j][0] + c2.sequence_[j][0];
			out.sequence_[j][1] = out.sequence_[j][1] + c2.sequence_[j][1];
		}
		return out;
    // If c2 > c1 use a copy constructor to make a copy of c2 and add c1 to it
	}else{
		Points2D out = c2;
	 	for(size_t j = 0; j < c1.size(); ++j){
			out.sequence_[j][0] = out.sequence_[j][0] + c1.sequence_[j][0];
			out.sequence_[j][1] = out.sequence_[j][1] + c1.sequence_[j][1];	 	
	 	}
	 	return out;	
	}
  }

 // Overloading the << operator.
  friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2){
    // Print () if the size is 0
    if (some_points2.size_ == 0) {
          out << "()";
    }
    // Othervise print all the points in the object
    for(size_t i = 0; i < some_points2.size_; ++i){		
      out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ") ";
    }
    out << std::endl;
    return out;
  }
 
 private:
  // Sequence of points. 
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2D_H_
