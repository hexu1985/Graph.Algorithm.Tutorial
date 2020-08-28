/** \example sample_unweight_graph_dfs1.cpp
 * This is an example of how to use the unweight::DFS class.
 */

#include <vector>
#include "unweight_sparse_multi_graph.hpp"
#include "unweight_graph_utils.hpp"
#include "unweight_graph_dfs_iter.hpp"

using namespace std;
using namespace unweight;

using Edge = sparse_multi_graph::edge_type;
using Graph = sparse_multi_graph;

int main(int argc, char *argv[])
{
    int vertex_number = 8;
    vector<Edge> edges = {{0,2}, {0,5}, {0,7}, {1,7}, {2,6}, {3,4}, {3,5}, {4,5}, {4,6}, {4,7}};

    auto graph = make_graph<Graph>(vertex_number, edges);

    DFS<Graph> dfs(*graph);
    dfs.search(0);

    return 0;
}
