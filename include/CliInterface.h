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
    void define_relationship(); // TODO

    void print_is_connected_matrix() const;
    // void show_diagram() const; // TODO

    enum class MenuChoice : int8_t;
    MenuChoice get_user_menu_choice(); // TODO

    void change_personal_information(); // TODO
    void change_relationship_need_rebuild_connected(); // TODO

    static int initialize_user_count();

    // 作为初始化和修改用户的函数的核心部分

    int set_user_id_core();
    MyString set_user_name_core();
    Sex set_user_sex_core();
    int set_user_age_core();
    MyString set_user_job_core();

    inline void print_menu_choice(MenuChoice number, MyString content);

private:
    SocialNetwork social_network;

    enum class MenuChoice : int8_t
    {
        Quit = 0,
        PrintConnectedMatrix,
        // ShowDiagram,
        ChangePersonalInformation,
        ChangeRelationship,
        // AddUser,
        // DeleteUser,
    };
};

#endif // SOCIALBONDANALYSIS_CLIINTERFACE_H