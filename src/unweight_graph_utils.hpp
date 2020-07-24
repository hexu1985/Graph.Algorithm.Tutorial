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

}   // namespace unweight

#endif  // UNWEIGHT_DENSE_GRAPH_UTILS_INC
