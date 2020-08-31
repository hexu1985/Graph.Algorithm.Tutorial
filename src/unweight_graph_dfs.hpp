/**
 * @file unweight_graph_dfs.hpp
 * @brief  深度优先搜索(Depth-first Search, DFS)算法，递归版本
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-08-31
 */
#ifndef UNWEIGHT_GRAPH_DFS_INC
#define UNWEIGHT_GRAPH_DFS_INC

#include <vector>
#include <algorithm>

namespace unweight {

/**
 * @brief 深度优先搜索(Depth-first Search, DFS)算法，递归版本
 *
 * @tparam Graph 图类型
 */
template <typename Graph>
class DFS {
private:
    const Graph &graph_;
    std::vector<bool> visited_;

public:
    DFS(const Graph &graph): graph_(graph)
    {
    }

    void search(int s)
    {
        // 把所有顶点标记为未探索
        visited_.resize(graph_.vertex_count());
        std::fill(std::begin(visited_), std::end(visited_), false);

        explore(s);
    }

private:
    void explore(int s)
    {
        // 把s标记为已探索
        visited_[s] = true;

        // 遍历s的邻接列表
        for (auto v: graph_.get_adj_list(s)) {
            if (!visited_[v]) {
                explore(v);
            }
        }
    }
};

}   // namespace unweight

#endif



