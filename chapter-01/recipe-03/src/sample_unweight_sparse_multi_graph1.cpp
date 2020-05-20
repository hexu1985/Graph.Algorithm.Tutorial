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
    int vertex_number = 8;
    vector<Edge> edges = {{0,2}, {0,5}, {0,7}, {1,7}, {2,6}, {3,4}, {3,5}, {4,5}, {4,6}, {4,7}};

    auto graph = Graph::make_graph(vertex_number);

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
