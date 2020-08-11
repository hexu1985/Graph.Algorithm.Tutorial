/**
 * @file unweight_graph_ucc.hpp
 * @brief 无向图连通分量(Undigraph Connected Components, UCC)算法
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-08-07
 */
#ifndef UNWEIGHT_GRAPH_UCC_INC
#define UNWEIGHT_GRAPH_UCC_INC

#include <vector>
#include <queue>
#include <algorithm>

namespace unweight {

/**
 * @brief 无向图连通分量(Undigraph Connected Components, UCC)算法
 *
 * @tparam Graph 图类型
 */
template <typename Graph>
class UCC {
private:
    const Graph &graph_;
    std::vector<bool> visited_;
    std::vector<int> cc_;
    int num_cc_ = 0;

public:
    UCC(const Graph &graph): graph_(graph)
    {
    }

    void calculate()
    {
        // 把s标记为已探索，所有其他顶点标记为未探索
        visited_.resize(graph_.vertex_count());
        std::fill(std::begin(visited_), std::end(visited_), false);

        num_cc_ = 0;
        cc_.assign(graph_.vertex_count(), -1);

        for (int v = 0; v < graph_.vertex_count(); v++) {
            if (!visited_[v]) {
                search(v);
                num_cc_++;
            }
        }
    }

private:
    void search(int s)
    {
        visited_[s] = true;
        cc_[s] = num_cc_;

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
                    cc_[w] = num_cc_;
                    Q.push(w);
                }
            }
        }
    }
};

}   // namespace unweight

#endif

