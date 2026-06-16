#ifndef SOCIALBONDSANALYSIS_MYADJMAT_H
#define SOCIALBONDSANALYSIS_MYADJMAT_H

#include "MyQueue.h"
#include "MyVector.h"
#include <stdexcept>
#include <algorithm>

// 模板类的代码必须写在h文件中
template <typename T, T diag_default_value, T original_edge_value>
class MyAdjMat
{
    // 通过 typedef 提高代码可读性
    using Ptrlevel1 = T *;
    using Ptrlevel2 = T **;

public:
    MyAdjMat(int sideLength);
    ~MyAdjMat();
    // 不允许无参数构造；暂时不允许拷贝，这个以后可能会开发
    MyAdjMat() = delete;
    MyAdjMat(const MyAdjMat &) = delete;
    MyAdjMat &operator=(const MyAdjMat &) = delete;

    const int &getSideLength() const { return sideLength; }
    // 拷贝开销 vs 解引用开销
    void setSideLength(int sideLength) { this->sideLength = sideLength; }

    bool &get_has_done() { return has_done; }
    const bool &get_has_done() const { return has_done; }

    // 一个写一个改，分工明确

    // 最小数字为0，最大数字为sideLength - 1
    // 这个const必须写在参数表后面
    const T &get_element(int a, int b) const;

    void set_element(int a, int b, T value);

    // 这个函数是整个项目的核心，运用 bfs 算法。目前 bfs 和给元素赋值的操作是未解耦的。
    void build_connected_adjmat(MyAdjMat<T, diag_default_value, original_edge_value> &output);

private:
    int sideLength;
    Ptrlevel2 data;
    bool has_done; // 这一表示状态的变量可以避免对应之前状态的矩阵污染程序
};

template <typename T, T diag_default_value, T original_edge_value>
MyAdjMat<T, diag_default_value, original_edge_value>::MyAdjMat(int sideLength) : has_done(false)
{
    this->sideLength = sideLength;
    data = new Ptrlevel1[sideLength];

    // 为了节省空间和避免对称元不同带来的逻辑错误，我们只生成矩阵的下三角部分
    for (int i = 0; i < sideLength; i++)
    {
        data[i] = new T[i + 1]; // 注意这里的逻辑
        // 在通过循环生成矩阵的同时，自动将主对角元设置为主对角元默认值
        data[i][i] = diag_default_value;

        // 其余部分自动设置为 original_edge_value
        std::fill_n(data[i], i, original_edge_value);
    }
}

template <typename T, T diag_default_value, T original_edge_value>
MyAdjMat<T, diag_default_value, original_edge_value>::~MyAdjMat()
{
    for (int i = 0; i < sideLength; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

template <typename T, T diag_default_value, T original_edge_value>
const T &MyAdjMat<T, diag_default_value, original_edge_value>::get_element(int a, int b) const
{
    int row, column;
    if (a == b)
    {
        throw std::logic_error("不允许访问对角元的值");
    }
    else if (a < 0 || b < 0 || a >= sideLength || b >= sideLength)
    {
        throw std::logic_error("不允许越界访问");
    }
    else // max行，min列
    {
        row = a > b ? a : b;
        column = a < b ? a : b;
    }
    return data[row][column];
}
template <typename T, T diag_default_value, T original_edge_value>
void MyAdjMat<T, diag_default_value, original_edge_value>::set_element(int a, int b, T value)
{
    int row, column;
    if (a == b)
    {
        throw std::logic_error("不允许访问对角元的值");
    }
    else if (a < 0 || b < 0 || a >= sideLength || b >= sideLength)
    {
        throw std::logic_error("不允许越界访问");
    }
    else // max行，min列
    {
        row = a > b ? a : b;
        column = a < b ? a : b;
    }

    data[row][column] = value;
}

template <typename T, T diag_default_value, T original_edge_value>
void MyAdjMat<T, diag_default_value, original_edge_value>::build_connected_adjmat(MyAdjMat<T, diag_default_value, original_edge_value> &output)
{
    enum class NodeState : uint8_t
    {
        Unvisited = 0,
        InCurrentCircle = 1,
        InDifferentCircle = 2
    };

    if (this->has_done == false)
    {
        throw std::logic_error("现在该矩阵还未完成，不能搭建 connected_adjmat ！");
    }

    if (output.get_has_done() == true)
    {
        output.get_has_done() = false;
    }
    // int 存储用户编号
    MyQueue<int> open;
    // 用 MyVector<NodeState> node_state 构造closed表，空间换时间，同时使逻辑简单
    MyVector<NodeState> node_state(sideLength, NodeState::Unvisited);

    // 每次循环进行一个“相连朋友圈”的完整搜索
    // 各层用循环，直接写好初始化、循环条件和状态转移
    for (int start = 0; start < sideLength; start++)
    {
        // 不是合适起点就跳过，用这种简单逻辑就可实现start的更新
        if (node_state[start] != NodeState::Unvisited)
            continue;

        open.push(start);
        node_state[start] = NodeState::InCurrentCircle; // 遵循下面的规则。但这是初始化，因此必须补上

        while (!open.isEmpty())
        {
            int curr = open.front();
            open.pop(); // 队头数据已经失去利用价值（或者说已经转移到curr中），必须弹出
            // 如果这一步以后队列已经空了，那么整个循环体会执行完，然后跳出

            // i 一定要遍历整个 sideLength 吗？
            for (int i = 0; i < sideLength; i++)
            {
                // 如果探索与自己的关系那么就什么都不做
                // 这里改为用反向条件包裹，符合规范
                if (i != curr)
                {
                    if (node_state[i] == NodeState::InDifferentCircle)
                        output.set_element(i, curr, false);
                    else if (node_state[i] == NodeState::InCurrentCircle)
                        output.set_element(i, curr, true);
                    // 如果是邻居且未探究过，那么要进入open表，且必然相连；
                    // 如果i节点未探索过，那么什么都不知道，这一关系在当前i节点后续程序中成为curr节点时才能得以知晓
                    else if (this->get_element(i, curr) == true) // && node_state[i] == NodeState::Unvisited
                    {
                        output.set_element(i, curr, true);
                        // 只有未探索过的节点才能被push进open表中
                        open.push(i);

                        // 入队以后元素就已经是closed了（InCurrentCircle）
                        // 如果不这样规定：若open表中排在前位的元素也与这个新推入的元素相连，那么该元素必然被重复推入open表中
                        // 这意味着后面 每一个 curr 状态都是 InCurrentCircle， 因此之前的curr的状态设置可以删掉了
                        node_state[i] = NodeState::InCurrentCircle;
                    }
                }
            }
        }

        // 这一部分负责状态转移 ：当前朋友圈对于下一次探索来说是别的朋友圈
        for (int i = 0; i < sideLength; i++)
        {
            if (node_state[i] == NodeState::InCurrentCircle)
            {
                node_state[i] = NodeState::InDifferentCircle;
            }
        }
    }

    output.has_done = true;
}

#endif // SOCIALBONDSANALYSIS_MYADJMAT_H