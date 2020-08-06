/**
 * @file unweight_graph_dot.hpp
 * @brief 将图转成dot格式
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-08-06
 */
#ifndef UNWEIGHT_GRAPH_DOT_INC
#define UNWEIGHT_GRAPH_DOT_INC

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "unweight_graph_utils.hpp"

namespace unweight {

/**
 * @brief 将图转成DOT语言格式
 *
 * @tparam Graph 图类型
 * @tparam VMap map类型：int -> string
 * @param strm 输出流
 * @param graph 指定图
 * @param vmap 顶点index到顶点name的map
 */
template <typename Graph, typename VMap>
void write_dot(std::ostream &strm, const Graph &graph, const VMap &vmap) 
{
    bool is_digraph = graph.is_directed();
    std::string title = is_digraph ? "digraph G" : "graph G";
    std::string line_symbol = is_digraph ? "->" : "--";

    strm << title << " {\n";

    // 打印点集
    for (auto v: get_vertexes(graph)) {
        strm << "\t" << vmap[v] << ";\n";
    }

    // 打印边集
    for (auto e: get_edges(graph)) {
        auto [u, v] = e;
        strm << "\t" << vmap[u] << line_symbol << vmap[v] << ";\n";
    }

    strm << "}\n";
}

template <typename Graph, typename VMap>
std::string to_dot(const Graph &graph, const VMap &vmap)
{
    std::ostringstream os;
    write_dot(os, graph, vmap);
    return os.str();
}

template <typename Graph, typename VMap>
bool save_dot_file(const char *dot_file, const Graph &graph, const VMap &vmap) 
{
    std::ofstream ofile(dot_file);
    if (!ofile) {
        std::cout << "open " << dot_file << " failed!\n";
        return false;
    }

    write_dot(ofile, graph, vmap);
    return true;
}

}   // namespace unweight

#endif  // UNWEIGHT_DENSE_GRAPH_DOT_INC
