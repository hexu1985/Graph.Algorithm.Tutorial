/**
 * @file unweight_digraph_topo_sort.hpp
 * @brief 有向图拓扑排序算法
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-09-03
 */
#ifndef UNWEIGHT_DIGRAPH_TOPO_SORT_INC
#define UNWEIGHT_DIGRAPH_TOPO_SORT_INC

#include <vector>
#include <algorithm>

namespace unweight {

/**
 * @brief 有向图拓扑排序算法
 *
 * @tparam Graph 图类型
 */
template <typename Graph>
class TopoSort {
private:
    const Graph &graph_;
    std::vector<bool> visited_;
    int cur_label_;         // 记录顺序
    std::vector<int> f_;    // 每个顶点的顺序

public:
    TopoSort(const Graph &graph): graph_(graph)
    {
    }

    void sort()
    {
        // 把所有顶点标记为未探索
        visited_.resize(graph_.vertex_count());
        std::fill(std::begin(visited_), std::end(visited_), false);

        f_.assign(graph_.vertex_count(), -1);

        cur_label_ = graph_.vertex_count();

        for (int v = 0; v < graph_.vertex_count(); v++) {
            if (!visited_[v]) {
                dfs_topo(v);
            }
        }
    }

private:
    void dfs_topo(int s)
    {
        // 把s标记为已探索
        visited_[s] = true;

        // 遍历s的邻接列表
        for (auto v: graph_.get_adj_list(s)) {
            if (!visited_[v]) {
                dfs_topo(v);
            }
        }
        f_[s] = cur_label_;             // s的位置符合顺序
        cur_label_ = cur_label_ - 1;    // 从右向左进行操作
    }
};

}   // namespace unweight

#endif
