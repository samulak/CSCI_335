// Adam Samulak
//**Graph Class *//
// Creates directed graphs out of vertex structs. It allows for finding connected
// vertices as well as finding the shortest path by the use of Dijkstra algorithm.

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"
#include<iostream>
#include<vector>
#include<list>
#include <iterator>
#include <typeinfo>
#include <limits>
#include <stack>
using namespace std;

// Vertex implementation.
//
// *************NEW PUBLIC OPERATIONS***********************
// Add_connection( )         --> adds a pair to a adjacency list (Connected vertex, weight)
// ************* END NEW PUBLIC OPERATIONS***********************

struct Vertex{
  void Add_connection(const int vertex, const float weight){
    adj_lst.push_back(make_pair(vertex, weight));
  }// End Add_connection

 list<pair<int, float>> adj_lst; //
 bool known_ = false;
 float distance_ = numeric_limits<float>::max();
 int parrent_vertex = 0;
 Vertex * previous_in_path = nullptr;
}; // End struct Vertex

// Graph implementation.
//
// *************NEW PUBLIC OPERATIONS***********************
// Graph( )         --> resizes the vector and adds empty vertices to it
// Insert( )        --> adds a new pair to the adjacency list in the vertex
// Connected( )     --> prints out all connected vertices
// Dijkstra( )      --> finds the shorthest path and prints it out
// ************* END NEW PUBLIC OPERATIONS***********************

class Graph{
public:
  Graph(const int size){
    vertex_vec.resize(size + 1);
    for (size_t i = 0; i < vertex_vec.size(); i++) {
      vertex_vec[i] = new Vertex();
      vertex_vec[i]->parrent_vertex = i;
    }// End for
  }// End Graph

  void Insert(const int vertex, const int connected_ver, const float weight){
    vertex_vec[vertex]->Add_connection(connected_ver, weight);
  }// End Insert

  void Connected(const int vert, const int conn_ver){
      bool found = false;
      for( auto & element : vertex_vec[vert]->adj_lst){
        if (element.first == conn_ver) {
          cout << vert << ' ' << conn_ver << ": connected " << element.second << endl;
          found = true;
          exit;
        }// End if
      }// End for
      if (!found)
        cout << vert << ' ' << conn_ver << ": not_connected "  << endl;

  }// End Connected

  void Dijkstra(const int first_vertex){
    // Set the fits distance to 0.
    vertex_vec[first_vertex]->distance_ = 0;
    // Create the binary heap to keep track of the vertices.
    BinaryHeap<Vertex*> vertex_que;
    vertex_que.insert(vertex_vec[first_vertex]);
    // Bool var for tracking repetitions in the binary heap.
    bool found = false;

    // Main while loop that goes through the whole graph
    // and finds the shortest path.
    while(!vertex_que.isEmpty()){
      Vertex* ver;
      // While deletes repetitions from the binary heap
      while (!vertex_que.isEmpty() && !found) {
        if (!vertex_que.isEmpty() && !vertex_que.findMin()->known_) {
          ver = vertex_que.findMin();
          ver->known_ = true;
          vertex_que.deleteMin();
          found = true;
        } else {
          if (!vertex_que.isEmpty())
            vertex_que.deleteMin();
        }// End if else
      }// End nested while
      found = false;

      // Loop adjusts weights and finds a path for future back tracking
      for( auto & element : ver->adj_lst){
          if (ver->distance_ + element.second < vertex_vec[element.first]->distance_) {
            vertex_vec[element.first]->distance_ = ver->distance_ + element.second;
            vertex_vec[element.first]->previous_in_path = ver;
          }// End if

          if (!vertex_vec[element.first]->known_)
            vertex_que.insert(vertex_vec[element.first]);
      }// End for
    }// End while

    // Print section
    for (size_t i = 1; i < vertex_vec.size(); i++) {
      // Stack used to print the path in reverse order
      stack<int> tmp_stack;
      cout << i << ": ";
      Vertex* tmp = vertex_vec[i];

      while (tmp->previous_in_path != nullptr) {
        tmp_stack.push(tmp->parrent_vertex);
        tmp = tmp->previous_in_path;
      }// End while

      if (vertex_vec[i]->distance_ != numeric_limits<float>::max()) {
        tmp_stack.push(first_vertex);
        while (!tmp_stack.empty()) {
          cout << tmp_stack.top()<< " ";
          tmp_stack.pop();
        }// End while
        cout.precision(1);
        cout << fixed;
        std::cout << " cost: " << vertex_vec[i]->distance_ << std::endl;
      } else {
        cout << "not_possible" << endl;
      }// End if else
    }// End for
  }// End Dijkstra

private:
  vector<Vertex*> vertex_vec;
};// End class Graph
#endif
