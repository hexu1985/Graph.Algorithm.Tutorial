/**
 * @file unweight_graph_dfs_iter.hpp
 * @brief 深度优先搜索(Depth-first Search, DFS)算法，迭代式版本
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-08-28
 */
#ifndef UNWEIGHT_GRAPH_DFS_ITER_INC
#define UNWEIGHT_GRAPH_DFS_ITER_INC

#include <vector>
#include <stack>
#include <algorithm>

namespace unweight {

/**
 * @brief 深度优先搜索(Depth-first Search, DFS)算法，迭代式版本
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

        // Q := 一个堆栈数据结构，用s初始化
        std::stack<int> S;
        S.push(s);

        // 只要堆栈不为空，就一直处理
        while (!S.empty()) {
            // 从S的头部删除("弹出")顶点v
            auto v = S.top(); S.pop();

            // 如果v为未探索
            if (!visited_[v]) {
                // 把v标注为已探索
                visited_[v] = true;

                // 遍历v的邻接列表
                for (auto w: graph_.get_adj_list(v)) {
                    // 把w添加("压入")到S的头部
                    S.push(w);
                }
            }
        }
    }
};

}   // namespace unweight

#endif


