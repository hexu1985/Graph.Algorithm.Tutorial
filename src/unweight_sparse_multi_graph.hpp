/**
 * @file unweight_sparse_multi_graph.hpp
 * @brief 一个稀疏图实现, 基于邻接链表(支持平行边)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 *
 * @see C++算法: 图算法(第3版): 章节1.4
 */
#ifndef UNWEIGHT_SPARSE_MUTLI_GRAPH_INC
#define UNWEIGHT_SPARSE_MUTLI_GRAPH_INC

#include <tuple>
#include <memory>
#include <vector>
#include <forward_list>
#include <algorithm>

namespace unweight {

/**
 * @brief 一个稀疏图实现, 基于邻接链表(支持平行边)
 */
class sparse_multi_graph { 
public:
    /**
     * @brief 边类型
     */
    using edge_type = std::tuple<int, int>;

    /**
     * @brief 创建一条边
     *
     * @param u 起点
     * @param v 终点
     *
     * @return 边对象
     */
    static edge_type make_edge(int u, int v) 
    {
        return std::make_tuple(u, v);
    }

private:
	std::vector<std::forward_list<int>> adj_lists_;  // 邻接链表数组
	int v_cnt_ = 0;                                  // 顶点数
    int e_cnt_ = 0;                                  // 边数
	bool directed_ = false;                          // 是否为有向图

public:
    /**
     * @brief 构造一个稀疏图对象
     *
     * @param v_cnt 图的顶点数
     * @param directed 是否为有向图
     */
	sparse_multi_graph(int v_cnt, bool directed = false) :
		adj_lists_(v_cnt), v_cnt_(v_cnt), e_cnt_(0), directed_(directed) 
	{ 
	}

    /**
     * @brief 返回图的顶点数
     *
     * @return 顶点个数
     */
	int vertex_count() const { return v_cnt_; }

    /**
     * @brief 返回图的边数
     *
     * @return 边的个数
     */
	int edge_count() const { return e_cnt_; }

    /**
     * @brief 是否为有向图
     *
     * @return 如果为有向图, 返回true, 否则为false
     */
	bool is_directed() const { return directed_; }

    /**
     * @brief 向图中插入一条边
     *
     * @param e 要插入的边
     */
	void insert(edge_type e)
	{ 
        auto [u, v] = e;
		adj_lists_[u].push_front(v);
		if (!directed_) adj_lists_[v].push_front(u);
		e_cnt_++;
	} 

    /**
     * @brief 从图中删除一条边
     *
     * @param e 要删除的边
     */
	void remove(edge_type e)
	{
        auto [u, v] = e;
        int n = std::count(std::begin(adj_lists_[u]),
                    std::end(adj_lists_[u]), v);

        if (n == 0) return;

		e_cnt_-=n;
        adj_lists_[u].remove(v);

		if (!directed_) adj_lists_[v].remove(u);
	} 

    /**
     * @brief 判断边是否属于指定图
     *
     * @param e 边
     *
     * @return 如果边属于指定图, 返回true, 否则返回false
     */
	bool has_edge(edge_type e) const
	{
        auto [u, v] = e;
        return (std::find(std::begin(adj_lists_[u]),
                        std::end(adj_lists_[u]), v) != std::end(adj_lists_[u]));
	}

    /**
     * @brief 获取指定顶点的邻接顶点的列表
     *
     * @param v 指定顶点
     *
     * @return 邻接顶点的迭代器
     */
    const std::forward_list<int> &get_adj_list(int v) const 
    { 
        return adj_lists_[v]; 
    }

    /**
     * @brief 创建有向图
     *
     * @param v_cnt 顶点个数
     *
     * @return 有向图对象
     */
    static std::shared_ptr<sparse_multi_graph> make_digraph(int v_cnt)
    {
        return std::make_shared<sparse_multi_graph>(v_cnt, true);
    }

    /**
     * @brief 创建无向图
     *
     * @param v_cnt 顶点个数
     *
     * @return 无向图对象
     */
    static std::shared_ptr<sparse_multi_graph> make_graph(int v_cnt)
    {
        return std::make_shared<sparse_multi_graph>(v_cnt);
    }
};

/**
 * @brief 获取指定图的点集
 *
 * @param graph 指定图
 *
 * @return 点集
 */
std::vector<int> get_vertexes(const sparse_multi_graph &graph)
{
    std::vector<int> vertexes;
    int n = graph.vertex_count();
    for (int i = 0; i < n; i++) {
        vertexes.push_back(i);
    }
    return vertexes;
}

/**
 * @brief 获取指定图的边集
 *
 * @param graph 指定图
 *
 * @return 边集
 */
std::vector<sparse_multi_graph::edge_type> get_edges(const sparse_multi_graph &graph)
{
    std::vector<sparse_multi_graph::edge_type> edges;
    for (auto v: get_vertexes(graph)) {
        for (auto w: graph.get_adj_list(v)) {
            if (graph.is_directed() || v < w) {
                edges.push_back(sparse_multi_graph::make_edge(v, w));
            }
        }
    }

    return edges;
}
}   // namespace unweight

#endif
