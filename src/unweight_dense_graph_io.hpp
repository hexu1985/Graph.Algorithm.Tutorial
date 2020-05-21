/**
 * @file unweight_dense_graph_io.hpp
 * @brief 稠密图的输入输出运算符重载
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-05-19
 */
#ifndef UNWEIGHT_DENSE_GRAPH_IO_INC
#define UNWEIGHT_DENSE_GRAPH_IO_INC

#include <cmath>
#include <iostream>
#include <iomanip>
#include "unweight_dense_graph.hpp"
#include "unweight_dense_graph_utils.hpp"

namespace unweight {

/**
 * @brief 稠密图的输出运算符重载
 *
 * @param strm 输出流
 * @param graph 稠密图
 *
 * @return 输出流
 */
inline
std::ostream &operator <<(std::ostream &strm, const dense_graph &graph)
{
    int width = static_cast<int>(log10(graph.vertex_count()))+1;
    for (auto v: get_vertexes(graph)) {
        strm << std::setw(width) << v << ":";
        bool first = true;
        for (auto w: graph.get_adj_list(v)) {
            strm << (first ? " " : ", ") << w;
            first = false;
        }
        strm << std::endl;
    }

    return strm;
}

}   // namespace unweight

#endif  // UNWEIGHT_DENSE_GRAPH_IO_INC
