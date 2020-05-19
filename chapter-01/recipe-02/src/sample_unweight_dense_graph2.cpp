/** \example sample_unweight_dense_graph1.cpp
 * This is an example of how to use the unweight::dense_graph class.
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "unweight_dense_graph.hpp"
#include "unweight_dense_graph_dot.hpp"

using namespace std;
using namespace unweight;

using Edge = dense_graph::edge_type;
using Graph = dense_graph;

int main(int argc, char *argv[])
{
    string dot_file = "dense_graph.dot";
    if (argc >= 2) {
        dot_file = argv[1];
    }

    int vertex_number = 8;
    vector<Edge> edges = {{0,2}, {0,5}, {0,7}, {1,7}, {2,6}, {3,4}, {3,5}, {4,5}, {4,6}, {4,7}};

    auto graph = Graph::make_graph(vertex_number);

    cout << "insert edges\n";
    for (auto edge: edges)
        graph->insert(edge);

    // show edges
    cout << graph->edge_count() << " edges in graph" << endl;

    cout << "graph to dot format:\n"
        << to_dot(*graph)
        << endl;

    // save dot file
    cout << "save graph to " << dot_file << " ...\n";
    ofstream ofile(dot_file);
    if (!ofile) {
        cout << "open " << dot_file << " failed!\n";
        exit(1);
    }

    write_dot(ofile, *graph);

    cout << "write dot file success!" << endl;

    return 0;
}
