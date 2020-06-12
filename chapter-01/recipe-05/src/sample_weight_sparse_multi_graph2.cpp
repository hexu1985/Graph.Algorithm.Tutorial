/** \example sample_weight_sparse_multi_graph2.cpp
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
    string dot_file = "sparse_multi_graph.dot";
    if (argc >= 2) {
        dot_file = argv[1];
    }

    int vertexNumber = 8;
    vector<Edge> edges = {
        {0,6, .51}, 
        {0,1, .32}, 
        {0,2, .29}, 
        {4,3, .34}, 
        {5,3, .18}, 
        {7,4, .46},
        {5,4, .40}, 
        {0,5, .60}, 
        {6,4, .51}, 
        {7,0, .31}, 
        {7,6, .25},
        {7,1, .21} 
    };

    auto graph = Graph::make_graph(vertexNumber); 

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
