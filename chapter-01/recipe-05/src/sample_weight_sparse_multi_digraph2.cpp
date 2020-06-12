/** \example sample_weight_sparse_multi_digraph2.cpp
 * This is an example of how to use the weight::sparse_multi_graph class.
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "weight_sparse_multi_graph.hpp"
#include "weight_sparse_multi_graph_dot.hpp"

using namespace std;
using namespace weight;

using Edge = sparse_multi_graph::edge_type;
using Graph = sparse_multi_graph;

int main(int argc, char *argv[])
{
    string dot_file = "sparse_multi_digraph.dot";
    if (argc >= 2) {
        dot_file = argv[1];
    }

    int vertexNumber = 6;
    vector<Edge> edges = {
        {0,1, .41},
        {1,2, .51},
        {2,3, .50},
        {4,3, .36},
        {3,5, .38},
        {3,0, .45},
        {0,5, .29},
        {5,4, .21},
        {1,4, .32},
        {4,2, .32},
        {5,1, .29}
    };

    auto graph = Graph::make_digraph(vertexNumber);

    cout << "insert edges\n";
    for (auto &edge: edges)
        graph->insert(&edge);

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
