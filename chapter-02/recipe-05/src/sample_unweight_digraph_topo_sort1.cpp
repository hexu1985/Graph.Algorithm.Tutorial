/** \example sample_unweight_digraph_topo_sort1.cpp
 * This is an example of how to use the unweight::TopoSort class.
 */

#include <vector>
#include "unweight_sparse_multi_graph.hpp"
#include "unweight_graph_utils.hpp"
#include "unweight_digraph_topo_sort.hpp"

using namespace std;
using namespace unweight;

using Edge = sparse_multi_graph::edge_type;
using Graph = sparse_multi_graph;

int main(int argc, char *argv[])
{
    int vertex_number = 4;
    vector<Edge> edges = {{0,1}, {0,2}, {1,3}, {2,3}};

    auto graph = make_digraph<Graph>(vertex_number, edges);

    TopoSort<Graph> topo_sort(*graph);
    topo_sort.sort();

    return 0;
}
