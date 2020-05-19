/**
 * @file unweight_dense_graph_io.hpp
 * @brief 稠密图的输入输出运算符重载
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2020-05-19
 */
#ifndef UNWEIGHT_DENSE_GRAPH_IO_INC
#define UNWEIGHT_DENSE_GRAPH_IO_INC

#include <iostream>
#include <iomanip>
#include "unweight_dense_graph.hpp"

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
    for (int v = 0; v < graph.vertex_count(); v++) {
        strm << std::setw(2) << v << ":";
        for (auto w: graph.get_adj_list(v)) {
            strm << std::setw(2) << w << " ";
        }
        strm << std::endl;
    }

    return strm;
}

}   // namespace unweight

#endif  // UNWEIGHT_DENSE_GRAPH_IO_INC
