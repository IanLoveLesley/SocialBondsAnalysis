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

class SocialNetwork {
    friend CurrAdjMat; // 体现社交网络类“有一个” (has a) 邻接矩阵的关系；省去调用函数的开销？
public:
    SocialNetwork() = delete; // 不允许无参数构造
    SocialNetwork(int num_of_users);
    ~SocialNetwork();
    // 暂时不允许拷贝
    SocialNetwork(const SocialNetwork&) = delete;
    SocialNetwork& operator=(const SocialNetwork&) = delete;
private:
    MyVector<Person> user_list;
    CurrAdjMat is_connected;
    int num_of_users;
};


#endif //SOCIALBONDSANALYSIS_SOCIALNETWORK_H