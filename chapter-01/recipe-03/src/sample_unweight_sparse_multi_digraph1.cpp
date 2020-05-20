/** \example sample_unweight_sparse_multi_graph1.cpp
 * This is an example of how to use the unweight::sparse_multi_graph class.
 */
#include <vector>
#include "unweight_sparse_multi_graph.hpp"
#include "unweight_sparse_multi_graph_io.hpp"

using namespace std;
using namespace unweight;

using Edge = sparse_multi_graph::edge_type;
using Graph = sparse_multi_graph;

int main()
{
    int vertex_number = 13;
    vector<Edge> edges = {
        {4,2}, {2,3}, {3,2}, {0,6}, {0,1},
        {2,0}, {11,12}, {12,9}, {9,10}, {9,11},
        {8,9}, {10,12}, {4,11}, {4,3}, {3,5},
        {7,8}, {8,7}, {5,4}, {0,5}, {6,4},
        {6,9}, {7,6}};

    auto graph = Graph::make_digraph(vertex_number);

    cout << "insert edges\n";
    for (auto edge: edges)
        graph->insert(edge);

    // show edges
    cout << graph->edge_count() << " edges in graph" << endl;

    // show adjLists
    cout << "graph after insert edges:\n"
        << *graph
        << endl;

    cout << "remove edges\n";
    for (auto edge: get_edges(*graph))
        graph->remove(edge);

    // show edges
    cout << graph->edge_count() << " edges in graph" << endl;

    // show adjLists
    cout << "graph after remove edges:\n"
        << *graph
        << endl;

    return 0;
}
