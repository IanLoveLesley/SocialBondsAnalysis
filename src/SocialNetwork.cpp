//
// Created by 16507 on 2026/6/3.
//

#include "../include/SocialNetwork.h"

SocialNetwork::SocialNetwork(int num_of_users_) : num_of_users(num_of_users_), is_neighbor(num_of_users_), is_connected(num_of_users_) {}

SocialNetwork::~SocialNetwork()
{
    is_connected.~MyAdjMat; // 将矩阵析构掉。我不写它是否也会被调用？
}