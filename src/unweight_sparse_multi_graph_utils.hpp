/**
 * @file unweight_sparse_multi_graph_utils.hpp
 * @brief 稀疏图的工具函数
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-05-21
 */

#ifndef UNWEIGHT_SPARSE_MUTLI_GRAPH_UTILS_INC
#define UNWEIGHT_SPARSE_MUTLI_GRAPH_UTILS_INC

#include <vector>
#include "unweight_sparse_multi_graph.hpp"

namespace unweight {

/**
 * @brief 获取指定图的点集
 *
 * @param graph 指定图
 *
 * @return 点集
 */
std::vector<int> get_vertexes(const sparse_multi_graph &graph)
{
    std::vector<int> vertexes;
    int n = graph.vertex_count();
    for (int i = 0; i < n; i++) {
        vertexes.push_back(i);
    }
    return vertexes;
}

/**
 * @brief 获取指定图的边集
 *
 * @param graph 指定图
 *
 * @return 边集
 */
std::vector<sparse_multi_graph::edge_type> get_edges(const sparse_multi_graph &graph)
{
    std::vector<sparse_multi_graph::edge_type> edges;
    for (auto v: get_vertexes(graph)) {
        for (auto w: graph.get_adj_list(v)) {
            if (graph.is_directed() || v < w) {
                edges.push_back(sparse_multi_graph::make_edge(v, w));
            }
        }
    }

    return edges;
}

}   // namespace unweight

#endif  // unweight
