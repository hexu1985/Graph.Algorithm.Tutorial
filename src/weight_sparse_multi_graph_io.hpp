/**
 * @file weight_sparse_multi_graph_io.hpp
 * @brief 带权重的稠密图的输入输出运算符重载
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-05-19
 */
#ifndef WEIGHT_SPARSE_MULTI_GRAPH_IO_INC
#define WEIGHT_SPARSE_MULTI_GRAPH_IO_INC

#include <cmath>
#include <iostream>
#include <iomanip>
#include "weight_sparse_multi_graph.hpp"
#include "weight_sparse_multi_graph_utils.hpp"

namespace weight {

/**
 * @brief 带权重的稠密图的输出运算符重载
 *
 * @param strm 输出流
 * @param graph 带权重的稠密图
 *
 * @return 输出流
 */
inline
std::ostream &operator <<(std::ostream &strm, const sparse_multi_graph &graph)
{
    int width = static_cast<int>(log10(graph.vertex_count()))+1;
    for (auto v: get_vertexes(graph)) {
        strm << std::setw(width) << v << ": ";
        bool first = true;
        for (auto e: graph.get_adj_list(v)) {
            strm << (first ? " " : ", ") << e->other(v) << "(" << e->weight() << ")";
            first = false;
        }
        strm << std::endl;
    }

    return strm;
}

}   // namespace weight

#endif  // WEIGHT_SPARSE_MULTI_GRAPH_IO_INC

