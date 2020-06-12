/**
 * @file weight_sparse_multi_graph_utils.hpp
 * @brief 带权稀疏密图的工具函数
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-05-21
 */

#ifndef WEIGHT_SPARSE_MULTI_GRAPH_UTILS_INC
#define WEIGHT_SPARSE_MULTI_GRAPH_UTILS_INC

#include <vector>
#include "weight_sparse_multi_graph.hpp"

namespace weight {

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
std::vector<sparse_multi_graph::edge_type *> get_edges(const sparse_multi_graph &graph)
{
    std::vector<sparse_multi_graph::edge_type *> edges;
    for (auto v: get_vertexes(graph)) {
        for (auto e: graph.get_adj_list(v)) {
            if (e->is_from(v))
                edges.push_back(e);
        }
    }

    return edges;
}

}   // namespace weight

#endif  // WEIGHT_SPARSE_MULTI_GRAPH_UTILS_INC
