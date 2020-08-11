/** \example sample_unweight_graph_ucc1.cpp
 * This is an example of how to use the unweight::UCC class.
 */

#include <vector>
#include "unweight_sparse_multi_graph.hpp"
#include "unweight_graph_utils.hpp"
#include "unweight_graph_ucc.hpp"

using namespace std;
using namespace unweight;

using Edge = sparse_multi_graph::edge_type;
using Graph = sparse_multi_graph;

int main(int argc, char *argv[])
{
    int vertex_number = 10;
    vector<Edge> edges = {
        {0,2}, {0,4}, {2,4}, {4,6}, {4,8}, {1,3}, {5,7}, {5,9},
    };

    auto graph = make_graph<Graph>(vertex_number, edges);

    UCC<Graph> ucc(*graph);
    ucc.calculate();

    return 0;
}
