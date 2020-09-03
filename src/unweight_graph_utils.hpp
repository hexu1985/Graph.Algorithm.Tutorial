/**
 * @file unweight_graph_utils.hpp
 * @brief 创建图的工具函数
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-07-24
 */

#ifndef UNWEIGHT_GRAPH_UTILS_INC
#define UNWEIGHT_GRAPH_UTILS_INC

#include <memory>
#include <vector>

namespace unweight {

/**
 * @brief 创建无向图
 *
 * @tparam Graph 图的类型
 * @param v_cnt 顶点个数
 * @param edges 边列表
 *
 * @return 图的对象
 */
template <typename Graph>
std::shared_ptr<Graph> make_graph(int v_cnt, const std::vector<typename Graph::edge_type> &edges)
{
    auto graph = Graph::make_graph(v_cnt);

    for (auto edge: edges)
        graph->insert(edge);

    return graph;
}

/**
 * @brief 创建有向图
 *
 * @tparam Graph 图的类型
 * @param v_cnt 顶点个数
 * @param edges 边列表
 *
 * @return 图的对象
 */
template <typename Graph>
std::shared_ptr<Graph> make_digraph(int v_cnt, const std::vector<typename Graph::edge_type> &edges)
{
    auto graph = Graph::make_digraph(v_cnt);

    for (auto edge: edges)
        graph->insert(edge);

    return graph;
}

/**
 * @brief 获取指定图的点集
 *
 * @param graph 指定图
 *
 * @return 点集
 */
template <typename Graph>
std::vector<int> get_vertexes(const Graph &graph)
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
template <typename Graph>
std::vector<typename Graph::edge_type> get_edges(const Graph &graph)
{
    std::vector<typename Graph::edge_type> edges;
    for (auto v: get_vertexes(graph)) {
        for (auto w: graph.get_adj_list(v)) {
            if (graph.is_directed() || v < w) {
                edges.push_back(Graph::make_edge(v, w));
            }
        }
    }

    return edges;
}

}   // namespace unweight

#endif  // UNWEIGHT_DENSE_GRAPH_UTILS_INC
