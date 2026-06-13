#include "../include/MyQueue.h"
#include "../include/MyString.h"
#include "../include/MyVector.h"
#include "../include/Sex.h"
#include "../include/Person.h"
#include "../include/SocialNetwork.h"
#include <iostream>
using namespace std;

// 题目要求是10，我们可以暂时放松，以便进行简单测试
constexpr int MAX_USERS = 5;

int main()
{
    // 在这里检查用户个数是否小于 MAX_USERS，以完成题目要求。
    // 未来可能会在社交网络类和邻接矩阵类中添加检查人数/边长大于0的内容。
    int num_of_users;

    for (bool is_break = false; !is_break;)
    {
        cout << "请输入用户个数（需要大于" << MAX_USERS << "）" << endl;
        cin >> num_of_users;
        if (num_of_users <= MAX_USERS)
            cout << "用户个数不应小于等于" << MAX_USERS << "，请重试" << endl;
        else
            is_break = true;
    }

    SocialNetwork social_network(num_of_users);

    // 建立好友关系（todo）

    //
    return 0;
}