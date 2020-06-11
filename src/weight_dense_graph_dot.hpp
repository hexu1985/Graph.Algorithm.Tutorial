/**
 * @file weight_dense_graph_dot.hpp
 * @brief 将稠密图转成dot格式
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-05-19
 */
#ifndef WEIGHT_DENSE_GRAPH_DOT_INC
#define WEIGHT_DENSE_GRAPH_DOT_INC

#include <iostream>
#include <string>
#include <sstream>
#include "weight_dense_graph.hpp"
#include "weight_dense_graph_utils.hpp"

namespace weight {

/**
 * @brief 将稠密图转成DOT语言格式
 *
 * @param strm 输出流
 * @param graph 指定图
 */
void write_dot(std::ostream &strm, const dense_graph &graph) 
{
    bool is_digraph = graph.is_directed();
    std::string title = is_digraph ? "digraph G" : "graph G";
    std::string line_symbol = is_digraph ? "->" : "--";

    strm << title << " {\n";

    // 打印点集
    for (auto v: get_vertexes(graph)) {
        strm << "\t" << v << ";\n";
    }

    // 打印边集
    for (auto e: get_edges(graph)) {
        auto [u, v] = e->get_vertexes();
        strm << "\t" 
            << u << line_symbol << v 
            << " [label=\"" << e->weight() << "\"]"
            << ";\n";
    }

    strm << "}\n";
}

std::string to_dot(const dense_graph &graph)
{
    std::ostringstream os;
    write_dot(os, graph);
    return os.str();
}

}   // namespace weight

#endif  // WEIGHT_DENSE_GRAPH_DOT_INC
