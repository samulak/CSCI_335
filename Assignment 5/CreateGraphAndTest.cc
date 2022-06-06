// Adam Samulak
// Reads two text files. First text file is converted into a directed graph.
// Second text is used to check for connections between vertices in the created
// graph.

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "graph.h"

using namespace std;

int graphTestDriver(int argc, char **argv) {
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

  // Open the query file.
  ifstream text_query;
  text_query.open(argv[2]);
  string query;

  // Read in each vertex and a connected vertex to be searched for.
  // Search the graph.
  while (getline(text_query, query)) {
    stringstream query_line(query);
    string ver, c_ver;
    query_line >> ver;
    query_line >> c_ver;
    directed_graph.Connected(stoi(ver), stoi(c_ver));
  }// End while
  text_query.close();
}

int main(int argc, char **argv) {
  if (argc != 3) {
	cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
	return 0;
  }
  graphTestDriver(argc, argv);
  return 0;
}
