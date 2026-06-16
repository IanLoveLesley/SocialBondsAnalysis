#ifndef SOCIALBONDANALYSIS_CLIINTERFACE_H
#define SOCIALBONDANALYSIS_CLIINTERFACE_H

#include "SocialNetwork.h"
#include <iostream>
using namespace std;
constexpr int MIN_USERS = 10;

class CliInterface
{
public:
    CliInterface();
    // 命令行界面实例化之后起到主要进程作用的函数
    void run();

private:
    SocialNetwork social_network;
    enum class MainMenuChoice : int8_t;
    enum class UserInfoChoice : int8_t;
    enum class RelationshipDefMethod : int8_t;

private:
    void initialize_users();
    void define_relationship();
    void define_relationship_need_rebuild_connected();

    void print_is_connected_matrix() const;
    // void show_diagram() const; // TODO

    MainMenuChoice get_user_menu_choice();

    void print_user_info() const;
    void change_personal_information();
    inline void change_single_relationship_core();

    static int initialize_user_count();

    // 作为初始化和修改用户的函数的核心部分

    int set_user_id_core();
    MyString set_user_name_core();
    Sex set_user_sex_core();
    int set_user_age_core();
    MyString set_user_job_core();

    template <typename enum_type>
    inline void print_menu_choice(enum_type number, MyString content);
};

#endif // SOCIALBONDANALYSIS_CLIINTERFACE_H