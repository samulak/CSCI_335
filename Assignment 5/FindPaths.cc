// Adam Samulak
// A text file is converted into a directed graph.
// Then Dijkstra agorithm is used to find the shortes path.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "graph.h"

using namespace std;

int pathfindDriver(int argc, char **argv) {

  // Open the graph file and use the numer of vertices to create
  // an empty graph.
  ifstream text_graph;
  text_graph.open(argv[1]);
  string vertices;
  getline(text_graph, vertices);
  Graph directed_graph(stoi(vertices));

  // Read in consecutive lines in order to add connections to each vertex
  // store the vertex in a string.
  while(getline(text_graph, vertices)){
    stringstream graph_line(vertices);
    string vertex;
    graph_line >> vertex;

    // Read connected vertex and its weight into strings and
    // insert it into the graph.
    while (graph_line) {
      string conn_ver, weight_ver;
      graph_line >> conn_ver;
      graph_line >> weight_ver;
      // Make sure no epmty line exists
      if(graph_line)
        directed_graph.Insert(stoi(vertex),stoi(conn_ver),stof(weight_ver));
    }// End nested while
  }// End while
  text_graph.close();

  // Find the shortest path.
  directed_graph.Dijkstra(stoi(argv[2]));

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
