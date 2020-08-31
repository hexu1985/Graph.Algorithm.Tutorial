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
#include <map>
#include <iostream>
#include <fstream>

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
    int visit_count_ = 0;       // 访问顺序计数
    using edge_type = typename Graph::edge_type;
    std::map<edge_type, int> visit_order_; 

public:
    UCC(const Graph &graph): graph_(graph)
    {
    }

    template <typename VMap>
    void calculate_and_save_dotfile(const char *dot_file, const VMap &vmap)
    {
        calculate();

        std::ofstream ofile(dot_file);
        if (!ofile) {
            std::cout << "open " << dot_file << " failed!\n";
            return;
        }

        write_dot(ofile, vmap);
    }

private:
    void calculate()
    {
        // 把s标记为已探索，所有其他顶点标记为未探索
        visited_.resize(graph_.vertex_count());
        std::fill(std::begin(visited_), std::end(visited_), false);

        num_cc_ = 0;
        cc_.assign(graph_.vertex_count(), -1);

        visit_count_ = 0;

        for (int v = 0; v < graph_.vertex_count(); v++) {
            if (!visited_[v]) {
                num_cc_++;
                search(v);
            }
        }
    }

    void search(int s)
    {
        visited_[s] = true;

        // Q := 一个队列数据结构，用s进行初始化
        std::queue<int> Q;
        Q.push(s);

        // 只要队列不为空，就一直处理
        while (!Q.empty()) {
            // 从Q的头部删除一个顶点，称之为v
            auto v = Q.front(); Q.pop();
            cc_[v] = num_cc_;

            // 遍历v的邻接列表
            for (auto w: graph_.get_adj_list(v)) {
                if (!visited_[w]) {
                    // 如果w为未探索，把w标记为已探索，并且把w添加到Q的尾部
                    visited_[w] = true;
                    visit_order_[edge_type(v,w)] = ++visit_count_;
                    Q.push(w);
                }
            }
        }
    }

    template <typename VMap>
    void write_dot(std::ostream &strm, const VMap &vmap) 
    {
        std::vector<std::string> color_list = {"red", "green", "cyan"};

        bool is_digraph = graph_.is_directed();
        std::string title = is_digraph ? "digraph G" : "graph G";
        std::string line_symbol = is_digraph ? "->" : "--";

        strm << title << " {\n";

        // 打印点集
        for (auto v: get_vertexes(graph_)) {
            strm << "\t" << vmap[v];
            strm << "["
                << " color="
                << color_list[cc_[v]%color_list.size()];
            strm << ", style=filled"
                << "]";
            strm << ";\n";
        }

        // 打印边集
        for (auto e: get_edges(graph_)) {
            auto [u, v] = e;
            strm << "\t" << vmap[u] << line_symbol << vmap[v];
            if (visit_order_.find(e) != visit_order_.end()) {
                strm << "["
                    << " label=\" #" << visit_order_[e] << "\"" 
                    << ", color=" << color_list[cc_[v]%color_list.size()]
                    << ", penwidth=3.0"
                    << " ]";
            }
            strm << ";\n";
        }

        strm << "}\n";
    }
};

}   // namespace unweight

#endif

