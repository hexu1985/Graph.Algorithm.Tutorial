/**
 * @file unweight_graph_dfs_iter_dot.hpp
 * @brief 深度优先搜索(Depth-first Search, DFS)算法，递归版本
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-08-28
 */
#ifndef UNWEIGHT_GRAPH_DFS_DOT_INC
#define UNWEIGHT_GRAPH_DFS_DOT_INC

#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <fstream>

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
    int visit_count_ = 0;       // 访问顺序计数
    std::vector<int> visit_order_; 
    using edge_type = typename Graph::edge_type;
    std::set<edge_type> visited_edges_; 

public:
    DFS(const Graph &graph): graph_(graph)
    {
    }

    template <typename VMap>
    void search_and_save_dotfile(int s, const char *dot_file, const VMap &vmap)
    {
        search(s);

        std::ofstream ofile(dot_file);
        if (!ofile) {
            std::cout << "open " << dot_file << " failed!\n";
            return;
        }

        write_dot(s, ofile, vmap);
    }

private:
    void search(int s)
    {
        // 把所有顶点标记为未探索
        visited_.resize(graph_.vertex_count());
        std::fill(std::begin(visited_), std::end(visited_), false);

        visit_count_ = 0;
        visit_order_.assign(graph_.vertex_count(), -1);

        explore(edge_type(s,s));
    }

    void explore(edge_type e)
    {
        auto [_, v] = e;
        visited_[v] = true;
        visit_order_[v] = visit_count_++;
        visited_edges_.insert(e);

        // 遍历v的邻接列表
        for (auto w: graph_.get_adj_list(v)) {
            if (!visited_[w]) {
                explore(edge_type(v, w));
            }
        }
    }

    template <typename VMap>
    void write_dot(int s, std::ostream &strm, const VMap &vmap) 
    {
        std::vector<std::string> color_list = {"red", "green", "cyan"};

        bool is_digraph = graph_.is_directed();
        std::string title = is_digraph ? "digraph G" : "graph G";
        std::string line_symbol = is_digraph ? "->" : "--";

        strm << title << " {\n";

        // 打印点集
        for (auto v: get_vertexes(graph_)) {
            strm << "\t" << vmap[v];
            if (visited_[v]) {
                strm << "["
                    << " label=\"" << vmap[v] << " (#" << visit_order_[v] << ")\", "
                    << " color=";
                if (s == v) {
                    strm << "yellow";
                } else if (visit_order_[v] > 0) {
                    strm << "green";
                }
                strm << ", style=filled"
                    << "]";
            } else {
                strm << "["
                    << " label=\"" << vmap[v] << "\"]";
            }
            strm << ";\n";
        }

        // 打印边集
        for (auto e: get_edges(graph_)) {
            auto [u, v] = e;
            strm << "\t" << vmap[u] << line_symbol << vmap[v];
            if (visited_edges_.find(e) != visited_edges_.end() ||
                (!is_digraph && visited_edges_.find(edge_type(v,u)) != visited_edges_.end())) {
                strm << "["
                    << "color=red" 
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

