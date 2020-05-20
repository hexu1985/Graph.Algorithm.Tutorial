/**
 * @file unweight_dense_graph.hpp
 * @brief 一个稠密图实现, 基于邻接矩阵(不支持平行边)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-24
 *
 * @see C++算法: 图算法(第3版): 章节1.3
 */
#ifndef UNWEIGHT_DENSE_GRAPH_INC
#define UNWEIGHT_DENSE_GRAPH_INC

#include <tuple>
#include <vector>
#include <memory>

namespace unweight {

/**
 * @brief 一个稠密图实现, 基于邻接矩阵(不支持平行边)
 */
class dense_graph { 
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
	std::vector<std::vector<bool>> adj_mat_;  // 邻接矩阵
	int v_cnt_ = 0;                           // 顶点数
    int e_cnt_ = 0;                           // 边数
	bool directed_ = false;                   // 是否为有向图

    /**
     * @brief 初始化邻接矩阵
     *
     * @param v_cnt 边个数
     */
    void init_adj_mat()
    {
        adj_mat_.resize(v_cnt_);
		for (int i = 0; i < v_cnt_; i++) 
			adj_mat_[i].assign(v_cnt_, false);
    }

public:
    /**
     * @brief 构造一个稠密图对象
     *
     * @param v_cnt 图的顶点数
     * @param directed 是否为有向图
     */
	dense_graph(int v_cnt, bool directed = false) :
		v_cnt_(v_cnt), e_cnt_(0), directed_(directed)
	{ 
        init_adj_mat();
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
		if (adj_mat_[u][v] == false) e_cnt_++;
		adj_mat_[u][v] = true;
		if (!directed_) adj_mat_[v][u] = true; 
	} 

    /**
     * @brief 从图中删除一条边
     *
     * @param e 要删除的边
     */
	void remove(edge_type e)
	{ 
        auto [u, v] = e;
		if (adj_mat_[u][v] == true) e_cnt_--;
		adj_mat_[u][v] = false;
		if (!directed_) adj_mat_[v][u] = false; 
	} 

    /**
     * @brief 判断两个顶点之间是否有直连边(两顶点是否邻接)
     *
     * @param u from顶点
     * @param v to顶点
     *
     * @return 如果u和v邻接, 返回true, 否则返回false
     */
	bool has_edge(edge_type e) const 
    { 
        auto [u, v] = e;
        return adj_mat_[u][v]; 
    }

    /**
     * @brief 可以遍历指定顶点的所有邻接节点的迭代器
     */
    struct adj_iterator: public std::iterator<std::forward_iterator_tag, int> {
        const std::vector<bool> *array_ = 0;
        int v_ = -1;

        adj_iterator(const std::vector<bool> *array): array_(array)
        {
            next();
        }

        adj_iterator(const std::vector<bool> *array, int v): array_(array), v_(v)
        {
        }

        void next()
        {
            auto &array = *array_;
            for (v_++ ; v_ < (int) array.size(); v_++)
                if (array[v_])
                    break;
        }

        int operator *() const
        {
            return v_;
        }

        adj_iterator &operator ++()
        {
            next();
            return *this;
        }

        adj_iterator operator ++(int)
        {
            adj_iterator tmp(*this);
            next();
            return tmp;
        }

        bool operator ==(const adj_iterator &rhs) const
        {
            return (this->array_ == rhs.array_ && this->v_ == rhs.v_);
        }

        bool operator !=(const adj_iterator &rhs) const
        {
            return !(*this == rhs);
        }
    };

    /**
     * @brief 指定顶点的所有邻接节点的列表
     */
    struct adj_list {
        adj_iterator first_;
        adj_iterator last_;

        adj_list(const std::vector<bool> &array): first_(&array), last_(&array, array.size()) {}

        adj_iterator begin() const { return first_; }

        adj_iterator end() const { return last_; }
    };

    /**
     * @brief 获取指定顶点的邻接顶点的迭代器
     *
     * @param v 指定顶点
     *
     * @return 邻接顶点的迭代器
     */
    adj_list get_adj_list(int v) const 
    {
        return adj_list(adj_mat_[v]); 
    }

    /**
     * @brief 创建有向图
     *
     * @param v_cnt 顶点个数
     *
     * @return 有向图对象
     */
    static std::shared_ptr<dense_graph> make_digraph(int v_cnt)
    {
        return std::make_shared<dense_graph>(v_cnt, true);
    }

    /**
     * @brief 创建无向图
     *
     * @param v_cnt 顶点个数
     *
     * @return 无向图对象
     */
    static std::shared_ptr<dense_graph> make_graph(int v_cnt)
    {
        return std::make_shared<dense_graph>(v_cnt);
    }
};

/**
 * @brief 获取指定图的点集
 *
 * @param graph 指定图
 *
 * @return 点集
 */
std::vector<int> get_vertexes(const dense_graph &graph)
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
std::vector<dense_graph::edge_type> get_edges(const dense_graph &graph)
{
    std::vector<dense_graph::edge_type> edges;
    for (auto v: get_vertexes(graph)) {
        for (auto w: graph.get_adj_list(v)) {
            if (graph.is_directed() || v < w) {
                edges.push_back(dense_graph::make_edge(v, w));
            }
        }
    }

    return edges;
}

}   // namespace unweight

#endif
