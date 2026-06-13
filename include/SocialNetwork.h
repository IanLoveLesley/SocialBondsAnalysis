//
// Created by 16507 on 2026/6/3.
//

#ifndef SOCIALBONDSANALYSIS_SOCIALNETWORK_H
#define SOCIALBONDSANALYSIS_SOCIALNETWORK_H

#include "Person.h"
#include "MyQueue.h"
#include "MyString.h"
#include "MyVector.h"
#include "MyAdjMat.h"

typedef MyAdjMat<bool, true> CurrAdjMat; // 便于一次性修改，如对角元需要从true 变为false 时

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

    // 根据不同依据建立is_neighbor的函数（todo）（false 2 true）

    // 寻找整张图的连接关系，根据is_neighbor 建立 is_connected （false 2 ture）
    void build_is_connected();

    // 服务于图结构表示的接口（todo）

    // 确认任意两个用户是否连接的搜索接口

private:
    int num_of_users;
    CurrAdjMat is_neighbor, is_connected;
    MyVector<Person> user_list;
};

#endif // SOCIALBONDSANALYSIS_SOCIALNETWORK_H