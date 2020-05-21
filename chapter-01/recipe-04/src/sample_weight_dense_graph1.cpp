/** \example sample_weight_dense_graph1.cpp
 * This is an example of how to use the weight::dense_graph class.
 */
#include <vector>
#include "weight_dense_graph.hpp"
#include "weight_dense_graph_io.hpp"

using namespace std;
using namespace weight;

using Edge = dense_graph::edge_type;
using Graph = dense_graph;

int main()
{
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
