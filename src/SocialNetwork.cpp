//
// Created by 16507 on 2026/6/3.
//

#include "../include/SocialNetwork.h"
#include <stdexcept>

// 因为矩阵还没初始化好，所以不能直接 build_is_connected()
SocialNetwork::SocialNetwork(int num_of_users_) : user_count(num_of_users_), is_neighbor(num_of_users_), is_connected(num_of_users_) {}

SocialNetwork::~SocialNetwork()
{
    is_neighbor.~MyAdjMat();
    is_connected.~MyAdjMat(); // 将矩阵析构掉。我不写它是否也会被调用？
}

void SocialNetwork::push_user(Person source)
{
    if (source.getAge() < 0)
    {
        throw std::invalid_argument("年龄必须是大于等于0的整数");
    }
    user_list.push_back(std::move(source));
}

bool SocialNetwork::is_users_connected(int user_0, int user_1)
{
    if (!is_neighbor.get_has_done())
    {
        throw std::logic_error("请先将is_neighbor矩阵设置好！");
    }

    if (!is_connected.get_has_done())
    {
        build_is_connected();
    }

    return is_connected.get_element(user_0, user_1);
}

bool SocialNetwork::is_users_neighbors(int user_0, int user_1)
{
    if (!is_neighbor.get_has_done())
    {
        throw std::logic_error("请先将is_neighbor矩阵设置好！");
    }

    return is_neighbor.get_element(user_0, user_1);
}