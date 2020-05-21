/**
 * @file weight_dense_graph.hpp
 * @brief 带权重的稠密图实现, 基于邻接矩阵(不支持平行边)
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-07-09
 *
 * @see C++算法: 图算法(第3版): 章节4.1
 */
#ifndef WEIGHT_DENSE_GRAPH_INC
#define WEIGHT_DENSE_GRAPH_INC

#include <vector>
#include <memory>

namespace weight {

/**
 * @brief 带权重的稠密图实现, 基于邻接矩阵(不支持平行边)
 */
class dense_graph { 
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

    /**
     * @brief 创建一条带权重的边
     *
     * @param u 起点
     * @param v 终点
     * @param weight 权重
     *
     * @return 边的指针
     */
    static std::shared_ptr<edge_type> make_edge(int u, int v, int weight=1)
    {
        return std::make_shared<edge_type>(u, v, weight);
    }

private:
	std::vector<std::vector<edge_type *>> adj_mat_;     // 邻接矩阵
	int v_cnt_ = 0;                                     // 顶点数
    int e_cnt_ = 0;                                     // 边数
	bool directed_ = false;                             // 是否为有向图

    /**
     * @brief 初始化邻接矩阵
     *
     * @param v_cnt 边个数
     */
    void init_adj_mat()
    {
        adj_mat_.resize(v_cnt_);
		for (int i = 0; i < v_cnt_; i++) 
			adj_mat_[i].assign(v_cnt_, nullptr);
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
	void insert(edge_type *e)
	{ 
        auto [u, v] = e->get_vertexes();
		if (adj_mat_[u][v] == nullptr) e_cnt_++;
		adj_mat_[u][v] = e;
		if (!directed_) adj_mat_[v][u] = e; 
	} 

    /**
     * @brief 从图中删除一条边
     *
     * @param e 要删除的边
     */
	void remove(edge_type *e)
	{ 
        auto [u, v] = e->get_vertexes();
		if (adj_mat_[u][v]) e_cnt_--;
		adj_mat_[u][v] = nullptr;
		if (!directed_) adj_mat_[v][u] = nullptr; 
	} 

    /**
     * @brief 判断两个顶点之间是否有直连边(两顶点是否邻接)
     *
     * @param u from顶点
     * @param v to顶点
     *
     * @return 如果u和v邻接, 返回边的指针, 否则返回空指针
     */
    edge_type *get_edge(int u, int v) const { return adj_mat_[u][v]; }

    /**
     * @brief 可以遍历指定顶点的所有邻接节点的迭代器
     */
    struct adj_iterator: public std::iterator<std::forward_iterator_tag, int> {
        const std::vector<edge_type *> *array_ = nullptr;
        int v_ = -1;

        adj_iterator(const std::vector<edge_type *> *array): array_(array)
        {
            next();
        }

        adj_iterator(const std::vector<edge_type *> *array, int v): array_(array), v_(v)
        {
        }

        void next()
        {
            auto &array = *array_;
            for (v_++ ; v_ < (int) array.size(); v_++)
                if (array[v_])
                    break;
        }

        edge_type *operator *() const
        {
            auto &array = *array_;
            return array[v_];
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

        adj_list(const std::vector<edge_type *> &array): first_(&array), last_(&array, array.size()) {}

        adj_iterator begin() const { return first_; }

        adj_iterator end() const { return last_; }
    };

    /**
     * @brief 获取指定顶点的邻接顶点的列表
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

}   // namespace weight

#endif  // WEIGHT_DENSE_GRAPH_INC
