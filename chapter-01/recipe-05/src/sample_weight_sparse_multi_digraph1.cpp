/** \example sample_weight_sparse_multi_digraph1.cpp
 * This is an example of how to use the weight::sparse_multi_graph class.
 */
#include <vector>
#include "weight_sparse_multi_graph.hpp"
#include "weight_sparse_multi_graph_io.hpp"

using namespace std;
using namespace weight;

using Edge = sparse_multi_graph::edge_type;
using Graph = sparse_multi_graph;

int main()
{
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
