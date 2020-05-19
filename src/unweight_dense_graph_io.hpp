#ifndef UNWEIGHT_DENSE_GRAPH_IO_INC
#define UNWEIGHT_DENSE_GRAPH_IO_INC

#include <iostream>
#include <iomanip>
#include "unweight_dense_graph.hpp"

namespace unweight {

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
