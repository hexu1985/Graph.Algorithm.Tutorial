/** \example sample_unweight_graph_dfs_iter_dot1.cpp
 * This is an example of how to use the unweight::DFS class.
 */

#include <string>
#include <vector>
#include <iostream>
#include "unweight_sparse_multi_graph.hpp"
#include "unweight_graph_utils.hpp"
#include "unweight_graph_dfs_iter_dot.hpp"
#include "unweight_graph_dot.hpp"

using namespace std;
using namespace unweight;

using Edge = sparse_multi_graph::edge_type;
using Graph = sparse_multi_graph;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " init.dot dfs.dot" << endl;
        return 1;
    }

    //                      0    1    2    3    4    5
    vector<string> vmap = {"s", "a", "b", "c", "d", "e"};
    vector<Edge> edges = {
                            {0,1}, // s - a
                            {0,2}, // s - b 
                            {1,3}, // a - c
                            {2,3}, // b - c
                            {2,4}, // b - d
                            {3,4}, // c - d
                            {3,5}, // c - e
                            {4,5}, // d - e
                         };
    int vertex_number = vmap.size();

    auto graph = make_graph<Graph>(vertex_number, edges);

    save_dot_file(argv[1], *graph, vmap);

    DFS<Graph> dfs(*graph);
    dfs.search_and_save_dotfile(0, argv[2], vmap);

    return 0;
}
