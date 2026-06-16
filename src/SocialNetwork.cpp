//
// Created by 16507 on 2026/6/3.
//

#include "../include/SocialNetwork.h"
#include <stdexcept>

// 因为矩阵还没初始化好，所以不能直接 build_is_connected_matrix()
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
        build_is_connected_matrix();
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

void SocialNetwork::change_single_relationship_with_check(int a, int b, bool value)
{
    if (is_neighbor.get_has_done()) // 如果是已经做好的即不能修改的
    {
        throw std::logic_error("不能修改不可修改的矩阵");
    }
    else if (a < 0 || a >= user_count || b < 0 || b >= user_count)
    {
        throw std::logic_error("访问越界：不能改变范围之外的用户！");
    }
    else if (a == b)
    {
        throw std::logic_error("不能改变邻接矩阵内部同一用户的数值");
    }
    else
    {
        is_neighbor.set_element(a, b, value);
        is_neighbor.get_has_done() = true;
    }
}

void SocialNetwork::build_relationship_according_to(const std::function<bool(int, int)> argument)
{
    if (is_neighbor.get_has_done()) // 如果是已经做好的即不能修改的
    {
        throw std::logic_error("不能修改不可修改的矩阵");
    }
    else
    {
        for (int i = 0; i < user_count; i++)
        {
            for (int j = 0; j < i; j++) // 不处理对角元（自己与自己的关系）
            {
                if (argument(i, j))
                {
                    is_neighbor.set_element(i, j, true); // 只能建立不能解除关系
                }
            }
        }
        is_neighbor.get_has_done() = true;
    }
}