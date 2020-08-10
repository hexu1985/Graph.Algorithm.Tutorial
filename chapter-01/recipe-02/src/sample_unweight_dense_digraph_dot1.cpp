/** \example sample_unweight_dense_graph1.cpp
 * This is an example of how to use the unweight::dense_graph class.
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "unweight_dense_graph.hpp"
#include "unweight_graph_dot.hpp"

using namespace std;
using namespace unweight;

using Edge = dense_graph::edge_type;
using Graph = dense_graph;

int main(int argc, char *argv[])
{
    string dot_file = "dense_digraph.dot";
    if (argc >= 2) {
        dot_file = argv[1];
    }

    //                      0    1    2    3    4    5
    vector<string> vmap = {"1", "2", "3", "4", "5", "6"};
    vector<Edge> edges = {
                            {0,1}, // 1 - 2
                            {0,3}, // 1 - 4 
                            {3,1}, // 4 - 2
                            {1,4}, // 2 - 5
                            {4,3}, // 5 - 4
                            {2,4}, // 3 - 5
                            {2,5}, // 3 - 6
                            {5,5}, // 6 - 6
                         };
    int vertex_number = vmap.size();

    auto graph = Graph::make_digraph(vertex_number);

    cout << "insert edges\n";
    for (auto edge: edges)
        graph->insert(edge);

    // show edges
    cout << graph->edge_count() << " edges in graph" << endl;

    // save dot file
    cout << "save graph to " << dot_file << " ...\n";
    save_dot_file(dot_file.c_str(), *graph, vmap);

    cout << "write dot file success!" << endl;

    return 0;
}
