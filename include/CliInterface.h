#ifndef SOCIALBONDANALYSIS_CLIINTERFACE_H
#define SOCIALBONDANALYSIS_CLIINTERFACE_H

#include "SocialNetwork.h"
#include <iostream>
using namespace std;

class CliInterface
{
public:
    CliInterface();
    // 命令行界面实例化之后起到主要进程作用的函数
    void run();

private:
    void initialize_users();
    void define_relationship();

    static int initialize_user_count();

    // 作为初始化和修改用户的函数的核心部分

    int set_user_id_core();
    MyString set_user_name_core();
    Sex set_user_sex_core();
    int set_user_age_core();
    MyString set_user_job_core();

private:
    SocialNetwork social_network;
};

#endif // SOCIALBONDANALYSIS_CLIINTERFACE_H