/** \example sample_unweight_graph_ucc_dot1.cpp
 * This is an example of how to use the unweight::UCC class.
 */

#include <string>
#include <vector>
#include <iostream>
#include "unweight_sparse_multi_graph.hpp"
#include "unweight_graph_utils.hpp"
#include "unweight_graph_ucc_dot.hpp"
#include "unweight_graph_dot.hpp"

using namespace std;
using namespace unweight;

using Edge = sparse_multi_graph::edge_type;
using Graph = sparse_multi_graph;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " init.dot ucc.dot" << endl;
        return 1;
    }

    //                      0    1    2    3    4    5    6    7    8    9
    vector<string> vmap = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    vector<Edge> edges = {
                            {0,2}, // 1 - 3
                            {0,4}, // 1 - 5
                            {2,4}, // 3 - 5
                            {4,6}, // 5 - 7
                            {4,8}, // 5 - 9
                            {1,3}, // 2 - 4
                            {5,7}, // 6 - 8
                            {5,9}, // 6 - 10
    };
    int vertex_number = vmap.size();

    auto graph = make_graph<Graph>(vertex_number, edges);

    save_dot_file(argv[1], *graph, vmap);

    UCC<Graph> ucc(*graph);
    ucc.calculate_and_save_dotfile(argv[2], vmap);

    return 0;
}
