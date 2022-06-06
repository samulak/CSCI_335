// Homework 4
// Testing Sorting Algorithms
// Adam Samulak

#include <algorithm>
#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Computes duration given a start time and a stop time in nano seconds.
// Keep it in.
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time,
			  chrono::high_resolution_clock::time_point end_time) {
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

// Test function that shows how you can time a piece of code.
// Just times a simple loop. Remove for final submission.

void TestTiming() {
  cout << "Test Timing" << endl;
  const auto begin_time = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end_time = chrono::high_resolution_clock::now();
  cout << ComputeDuration(begin_time, end_time) << "ns" << endl;

}

// Generates and returns random vector of size @size_of_vector.
// Initalizes a tmp vector and fill it with random numbers
// between 0 and 10000.
vector<int> GenerateRandomVector(size_t size_of_vector) {
    vector<int> tmp(size_of_vector);
    for(size_t i = 0; i < size_of_vector; i++){
			tmp[i] = rand() % 10000;
    }// End of for loop
    return tmp;
}// End of GenerateRandomVector

// Generates and returns sorted vector of size @size_of_vector.
// If @smaller_to_larger is true, returns vector sorted from small to large.
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
  vector<int> tmp_sorted(size_of_vector); // Not sure if this is the most efficient way to do it?
	for (size_t i = 0; i < size_of_vector; i++) {
		tmp_sorted[i] = i;
	}
  if(smaller_to_larger){
    return tmp_sorted;
  }else{
		sort(tmp_sorted.begin(), tmp_sorted.end(), greater<int>());
    return tmp_sorted;
  }// End of if
}// End of GenerateSortedVector

// Verifies that a vector is sorted given a comparator.
// I.e. it applies less_than() for consecutive pair of elements and returns true
// iff less_than() is true for all pairs.
// It checks for if the i-th and (i+1)-th item is both not less than and not equal.
// If that is the case it returns false in any other case it returns true.
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {
  for(size_t i = 0; i < input.size()-1; i++){
  	if(!less_than(input[i], input[i+1]) && input[i] != input[i+1])
			return false;
  }// End of for loop
  return true;
}// End of VerifyOrder

// Wrapper function to test different sorting algorithms. See homework's PDF for details.
void testSortingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);
  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
    cout << "Invalid input type" << endl;
    return;
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    return;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    return;
  }

  // This block of code to be removed for your final submission.
  //TestTiming();

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  vector<int> input_vector;
  if (input_type == "random") {
    input_vector = GenerateRandomVector(input_size);
  } else {
		if (input_type == "sorted_small_to_large")
      input_vector = GenerateSortedVector(input_size, true);
    else
      input_vector = GenerateSortedVector(input_size, false);
  }

	// Copy the vector into five vectors for Testing
	vector<int> heap_v = input_vector;
	vector<int> merge_v = input_vector;
	vector<int> quick_v = input_vector;
	vector<int> quick2_v = input_vector;
	vector<int> quick3_v = input_vector;

	// Set comparitor type
	if (comparison_type ==  "less") {
		auto begin = chrono::high_resolution_clock::now(); // Timer start
		HeapSort(heap_v, less<int>{}); 									// Sort
		auto end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "Heapsort" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(heap_v, less<int>{}) << endl;

		// Same patter for the rest of the tests
		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(merge_v, less<int>{}); 									// Sort
	  end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "MergeSort" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(merge_v, less<int>{}) << endl;

		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(quick_v, less<int>{}); 									// Sort
		end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "QuickSort" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(quick_v, less<int>{}) << endl;


  	cout << endl << "Testing Quicksort Pivot Implementations";

		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(quick_v, less<int>{}); 									// Sort
		end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "Median of Three" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(quick_v, less<int>{}) << endl;

		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(quick2_v, less<int>{}); 									// Sort
		end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "Middle" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(quick2_v, less<int>{}) << endl;

		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(quick3_v, less<int>{}); 									// Sort
		end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "First" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(quick3_v, less<int>{}) << endl;



	}else{
		auto begin = chrono::high_resolution_clock::now(); // Timer start
		HeapSort(heap_v, greater<int>{}); 									// Sort
		auto end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "Heapsort" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(heap_v, greater<int>{}) << endl;

		// Same patter for the rest of the tests
		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(merge_v, greater<int>{}); 									// Sort
	  end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "MergeSort" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(merge_v, greater<int>{}) << endl;

		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(quick_v, greater<int>{}); 									// Sort
		end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "Median of Three" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(quick_v, greater<int>{}) << endl;

		cout << endl << "Testing Quicksort Pivot Implementations";

		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(quick_v, greater<int>{}); 									// Sort
		end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "Median of Three" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(quick_v, greater<int>{}) << endl;

		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(quick2_v, greater<int>{}); 									// Sort
		end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "Middle" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(quick2_v, greater<int>{}) << endl;

		begin = chrono::high_resolution_clock::now(); // Timer start
		MergeSort(quick3_v, greater<int>{}); 									// Sort
		end = chrono::high_resolution_clock::now(); // Timer end

		cout << endl << "First" << endl << endl << "Runtime: <" << ComputeDuration(begin, end) << "> ns" << endl;
		cout << "Verified: " << VerifyOrder(quick3_v, greater<int>{}) << endl;


	}


}

int main(int argc, char **argv) {
  // DO NOT CHANGE or ADD ANY CODE in this function.
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }

  testSortingWrapper(argc, argv);

  return 0;
}
