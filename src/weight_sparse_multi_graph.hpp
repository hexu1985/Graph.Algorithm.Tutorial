/**
 * @file weight/SparsMultiGraph.hpp
 * @brief 一个稀疏图实现, 基于邻接链表(支持平行边)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-07-09
 *
 * @see C++算法: 图算法(第3版): 章节4.1
 */
#ifndef WEIGHT_SPARSE_MUTLI_GRAPH_INC
#define WEIGHT_SPARSE_MUTLI_GRAPH_INC

#include <vector>
#include <forward_list>
#include <algorithm>

namespace weight {

/**
 * @brief 一个稀疏图实现, 基于邻接链表(支持平行边)
 */
class sparse_multi_graph { 
public:
    /**
     * @brief 边类型
     */
    struct edge_type {
        int from_ = -1;
        int to_ = -1;
        double weight_ = 1;

        edge_type() = default;
        edge_type(int u, int v, double weight = 1): from_(u), to_(v), weight_(weight) {}

        /**
         * @brief 获取from顶点
         *
         * @return from顶点索引
         */
        int from() const { return from_; }

        /**
         * @brief 获取to顶点
         *
         * @return to顶点索引
         */
        int to() const { return to_; }

        /**
         * @brief 获取顶点对
         *
         * @return 顶点对
         */
        std::tuple<int, int> get_vertexes() const
        {
            return std::make_tuple(from_, to_);
        }

        /**
         * @brief 获取边权重
         *
         * @return 权重大小
         */
        double weight() const { return weight_; }

        /**
         * @brief 测试顶点是否为from顶点
         *
         * @param v 顶点索引
         *
         * @return 如果v为from顶点, 则返回true, 否则返回false
         */
        bool is_from(int v) { return v == from_; }

        /**
         * @brief 给定边的一个顶点, 返回另外一端顶点的索引
         *
         * @param v 给定的顶点
         *
         * @return 另外一端顶点的索引
         */
        int other(int v)
        {
            return is_from(v) ? to_ : from_;
        }
    };

private:
	std::vector<std::forward_list<edge_type *>> adj_lists_; // 邻接链表数组
	int v_cnt_ = 0;                                         // 顶点数
    int e_cnt_ = 0;                                         // 边数
	bool directed_ = false;                                 // 是否为有向图

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
	void insert(edge_type *e)
	{ 
        auto [u, v] = e->get_vertexes();
		adj_lists_[u].push_front(e);
		if (!directed_) adj_lists_[v].push_front(e);
		e_cnt_++;
	} 

    /**
     * @brief 从图中删除一条边
     *
     * @param e 要删除的边
     */
	void remove(edge_type *e)
	{
        auto [u, v] = e->get_vertexes();
        int n = std::count_if(std::begin(adj_lists_[u]),
                    std::end(adj_lists_[u]), 
                    [u, v](edge_type *e){ return e->other(u) == v;});

        if (n == 0) return;

		e_cnt_-=n;
        adj_lists_[u].remove_if([u, v](edge_type *e) { return e->other(u) == v; });

		if (!directed_)
            adj_lists_[v].remove_if([u, v](edge_type *e) { return (e->other(v) == u); });
	} 

    /**
     * @brief 判断两个顶点之间是否有直连边(两顶点是否邻接)
     *
     * @param u from顶点
     * @param v to顶点
     *
     * @return 如果u和v邻接, 返回边的指针, 否则返回空指针
     */
	edge_type *get_edge(int u, int v) const
	{
        for (auto e: adj_lists_[u]) {
            if (e->other(u) == v)
                return e;
        }
        return nullptr;
	}

    /**
     * @brief 获取指定顶点的邻接顶点的列表
     *
     * @param v 指定顶点
     *
     * @return 邻接顶点的迭代器
     */
    const std::forward_list<edge_type *> &get_adj_list(int v) const { return adj_lists_[v]; }

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

}   // namespace weight

#endif // WEIGHT_SPARSE_MULTI_GRAPH_INC
