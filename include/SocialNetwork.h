//
// Created by 16507 on 2026/6/3.
//

#ifndef SOCIALBONDSANALYSIS_SOCIALNETWORK_H
#define SOCIALBONDSANALYSIS_SOCIALNETWORK_H

#include <stdexcept>
#include "Person.h"
#include "MyQueue.h"
#include "MyString.h"
#include "MyVector.h"
#include "MyAdjMat.h"

using CurrAdjMat = MyAdjMat<bool, true, false>; // 增加一个抽象层，便于修改和维护；同时提高代码可读性

class SocialNetwork
{
public:
    SocialNetwork() = delete; // 不允许无参数构造
    // 只允许这种括号方式初始化，不允许等号形式的初始化或者隐式转换
    explicit SocialNetwork(int num_of_users_);
    ~SocialNetwork();
    // 暂时不允许拷贝
    SocialNetwork(const SocialNetwork &) = delete;
    SocialNetwork &operator=(const SocialNetwork &) = delete;

    const int get_user_count() const { return user_count; }

    void push_user(Person source);

    // 根据不同依据建立is_neighbor的函数

    enum class Mode
    {
    };
    void define_relationship();

    void neighbors_matrix_prepared() { is_neighbor.get_has_done() = true; }
    // is_neighbor矩阵被改动，则is_connected矩阵自然失效
    void neighbors_matrix_unprepared() { is_neighbor.get_has_done() = is_connected.get_has_done() = false; }

    // 寻找整张图的连接关系，根据is_neighbor 建立 is_connected
    inline void build_is_connected_matrix() { is_neighbor.build_connected_adjmat(is_connected); }

    // 服务于图结构表示的接口： 暂定直接返回整个is_neighbor矩阵的引用
    const CurrAdjMat& get_neighbor_matrix() const { return is_neighbor; }
    const CurrAdjMat& get_connected_matrix() const { return is_connected; }
    // 不允许直接操作；只允许通过 SocialNetwork类提供的接口操作
    CurrAdjMat& get_neighbor_matrix() = delete; 
    CurrAdjMat& get_connected_matrix() = delete;

    // 因为该函数可能会要求is_neighbor矩阵生成is_connected矩阵，所以该函数末尾不写const
    bool is_users_connected(int, int);
    bool is_users_neighbors(int, int);

private:
    int user_count;
    CurrAdjMat is_neighbor, is_connected;
    MyVector<Person> user_list;
};

#endif // SOCIALBONDSANALYSIS_SOCIALNETWORK_H