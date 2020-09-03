/** \example sample_unweight_digraph_topo_sort_dot1.cpp
 * This is an example of how to use the unweight::TopoSort class.
 */

#include <string>
#include <vector>
#include <iostream>
#include "unweight_sparse_multi_graph.hpp"
#include "unweight_graph_utils.hpp"
#include "unweight_digraph_topo_sort_dot.hpp"
#include "unweight_graph_dot.hpp"

using namespace std;
using namespace unweight;

using Edge = sparse_multi_graph::edge_type;
using Graph = sparse_multi_graph;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " init.dot topo_sort.dot" << endl;
        return 1;
    }

    //                      0    1    2    3 
    vector<string> vmap = {"s", "v", "w", "t"};
    vector<Edge> edges = {
                            {0,1}, // s - v
                            {0,2}, // s - w 
                            {1,3}, // v - t
                            {2,3}, // w - t
                         };
    int vertex_number = vmap.size();

    auto graph = make_digraph<Graph>(vertex_number, edges);

    save_dot_file(argv[1], *graph, vmap);

    TopoSort<Graph> topo_sort(*graph);
    topo_sort.sort_and_save_dotfile(argv[2], vmap);

    return 0;
}
