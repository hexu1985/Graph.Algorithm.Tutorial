/**
 * @file unweight_graph_bfs.hpp
 * @brief 宽度优先的搜索(Breadth-first Search, BFS)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-07-24
 */
#ifndef UNWEIGHT_GRAPH_BFS_INC
#define UNWEIGHT_GRAPH_BFS_INC

#include <vector>
#include <queue>
#include <algorithm>

namespace unweight {

/**
 * @brief 宽度优先的搜索(Breadth-first Search, BFS)
 *
 * @tparam Graph 图类型
 */
template <typename Graph>
class BFS {
private:
    const Graph &graph_;
    std::vector<bool> visited_;

public:
    BFS(const Graph &graph): graph_(graph)
    {
    }

    void search(int s)
    {
        // 把s标记为已探索，所有其他顶点标记为未探索
        visited_.resize(graph_.vertex_count());
        std::fill(std::begin(visited_), std::end(visited_), false);
        visited_[s] = true;

        // Q := 一个队列数据结构，用s进行初始化
        std::queue<int> Q;
        Q.push(s);

        // 只要队列不为空，就一直处理
        while (!Q.empty()) {
            // 从Q的头部删除一个顶点，称之为v
            auto v = Q.front(); Q.pop();

            // 遍历v的邻接列表
            for (auto w: graph_.get_adj_list(v)) {
                if (!visited_[w]) {
                    // 如果w为未探索，把w标记为已探索，并且把w添加到Q的尾部
                    visited_[w] = true;
                    Q.push(w);
                }
            }
        }
    }
};

}   // namespace unweight

#endif

