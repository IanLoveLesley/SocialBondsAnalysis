//
// Created by 16507 on 2026/6/3.
//

#include "../include/SocialNetwork.h"

SocialNetwork::SocialNetwork(int num_of_users): is_connected(num_of_users)
{
    this->num_of_users = num_of_users;
}

SocialNetwork::~SocialNetwork()
{
    is_connected.~MyAdjMat(); // 将矩阵析构掉。我不写它是否也会被调用？
}