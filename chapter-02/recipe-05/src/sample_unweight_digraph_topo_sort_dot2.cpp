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

    vector<string> vmap = {"内裤",  // 0
                           "裤子",  // 1
                           "腰带",  // 2
                           "衬衣",  // 3
                           "领带",  // 4
                           "夹克",  // 5
                           "袜子",  // 6
                           "鞋",    // 7 
                           "手表",  // 8
                           };
    vector<Edge> edges = {
                            {0, 1}, // 内裤 -> 裤子
                            {0, 7}, // 内裤 -> 鞋
                            {6, 7}, // 袜子 -> 鞋
                            {1, 7}, // 裤子 -> 鞋
                            {1, 2}, // 裤子 -> 腰带
                            {3, 2}, // 衬衣 -> 腰带
                            {3, 4}, // 衬衣 -> 领带
                            {4, 5}, // 领带 -> 夹克
                            {2, 5}, // 腰带 -> 夹克
                         };
    int vertex_number = vmap.size();

    auto graph = make_digraph<Graph>(vertex_number, edges);

    save_dot_file(argv[1], *graph, vmap);

    TopoSort<Graph> topo_sort(*graph);
    topo_sort.sort_and_save_dotfile(argv[2], vmap);

    return 0;
}
