#include "..\include\CliInterface.h"
#include <limits>

enum class CliInterface::MainMenuChoice : int8_t
{
    PrintConnectedMatrix = 1,
    // ShowDiagram,
    PrintUserInfo,
    ChangePersonalInformation,
    RedefineRelationship,
    // AddUser,
    // DeleteUser,
    Quit,
    count_plus_one // 这个用于计数；由于枚举开头是1不是传统的0，所以这里是plus_one
};
enum class CliInterface::UserInfoChoice : int8_t
{
    ID,
    Name,
    Sex,
    Age,
    Job,
    count_plus_one
};

enum class CliInterface::RelationshipDefMethod : int8_t
{
    SameAge = 1,
    AgeDifferenceWithin,
    SameSex,
    SameJob,
    Manually, // 手动操作——与其他模式不同，这个是唯一支持解除关系的
    // ClusterAlgo, // 未来拓展

    count_plus_one
};

CliInterface::CliInterface() : social_network(initialize_user_count()) {}

void CliInterface::run()
{
    bool is_running = true; // 通过设置这个状态参数为false来终止实例化的进程运行

    initialize_users();

    cout << "初始化：请建立好友关系" << endl;
    define_relationship_need_rebuild_connected(); // 初次定义

    social_network.build_is_connected_matrix();

    while (is_running)
    {
        MainMenuChoice choice = get_user_menu_choice();
        switch (choice)
        {
        case MainMenuChoice::Quit:
        {
            cout << "感谢使用，再见" << endl;
            is_running = false;
            break;
        }
        case MainMenuChoice::PrintConnectedMatrix:
        {
            print_is_connected_matrix();
            break;
        }
        case MainMenuChoice::PrintUserInfo:
        {
            print_user_info();
            break;
        }
        // case MainMenuChoice::ShowDiagram: { break; }
        case MainMenuChoice::ChangePersonalInformation:
        {
            change_personal_information();
            break;
        }
        case MainMenuChoice::RedefineRelationship:
        {
            define_relationship_need_rebuild_connected();
            social_network.build_is_connected_matrix();
            break;
        }
        // case MainMenuChoice::AddUser: { break; }
        // case MainMenuChoice::DeleteUser: { break; }
        default:
        {
            // 理论上这一行不可达，但是做好防御
            cout << "选项无效，请重新输入" << endl;
            break;
        }
        }
    }
}

// 这个函数属于整个类而非其中某个具体的对象
// 通过它与Cli界面类的构造函数的组合间接实现 social_network 的初始化
// 由于底层数据结构限制，一个进程内暂时无法改变用户数量（但可以随意改换每一个节点的信息以及相连关系）
int CliInterface::initialize_user_count()
{
    int temp;
    cout << "初始化：请输入社交网络用户个数（大于等于" << MIN_USERS << ")" << endl;

    while (true)
    {
        temp = my_safe_read_int();
        if (temp >= MIN_USERS) // (temp > 0) // 后面这个可能会换用
        {
            break;
        }
        else
        {
            cout << "社交网络用户个数必须大于等于" << MIN_USERS << endl;
        }
    }

    return temp;
}

void CliInterface::initialize_users()
{
    cout << "初始化社交网络内各个用户的信息" << endl;
    int num_of_users = social_network.get_user_count();
    for (int i = 0; i < num_of_users; i++)
    {
        cout << "请输入第" << i + 1 << "个用户的信息" << endl; // 依照用户习惯

        // 直接传入匿名临时对象； 所有的输入处理都以输出实参的函数形式呈现
        social_network.push_user(Person(set_user_id_core(), set_user_name_core(),
                                        set_user_sex_core(), set_user_age_core(), set_user_job_core()));
    }
}

void CliInterface::print_is_connected_matrix() const
{
    const CurrAdjMat &source = social_network.get_connected_matrix();
    const int user_count = social_network.get_user_count();

    // 打印列索引
    cout << ' ' << '\t';
    for (int i = 0; i < user_count; i++)
    {
        cout << i + 1 << '\t'; // 按照用户习惯，索引编号加上1
    }
    cout << endl;

    // 打印各行，包括行索引和矩阵内部信息
    for (int i = 0; i < user_count; i++)
    {
        cout << i + 1 << '\t';
        for (int j = 0; j < user_count; j++)
        {
            cout << source.get_element(i, j) << '\t';
        }
        cout << endl;
    }
}

CliInterface::MainMenuChoice CliInterface::get_user_menu_choice()
{
    // <cstdint> 中 int8_t 是 signed_char ，这意味着如果输入1，则会被处理为49
    // 因此必须改成int才能正确处理输入。
    int temp;
    while (true)
    {
        cout << "请选择您的操作" << endl;
        print_menu_choice<MainMenuChoice>(MainMenuChoice::PrintConnectedMatrix, "打印能间接转发状态的邻接矩阵");
        print_menu_choice<MainMenuChoice>(MainMenuChoice::PrintUserInfo, "打印用户信息");
        print_menu_choice<MainMenuChoice>(MainMenuChoice::ChangePersonalInformation, "修改用户信息");
        print_menu_choice<MainMenuChoice>(MainMenuChoice::RedefineRelationship, "修改好友关系");
        print_menu_choice<MainMenuChoice>(MainMenuChoice::Quit, "退出");

        temp = my_safe_read_int();// 如果输入数字在目录范围之外
        if (temp < 1 || temp >= static_cast<int8_t>(MainMenuChoice::count_plus_one))
        {
            cout << "选项无效，请重新输入" << endl;
        }
        else
        {
            break;
        }
    }
    return static_cast<MainMenuChoice>(temp);
}

void CliInterface::print_user_info() const
{
    while (true)
    {
        cout << "请输入要查询的用户的编号（从1开始，不超过用户总数）" << endl;
        int temp;
        temp = my_safe_read_int();
        temp--; // 改为计算机习惯的数字
        if (temp < 0 || temp >= social_network.get_user_count())
        {
            cout << "数字越界，请重新输入" << endl;
        }
        else
        {
            social_network.get_user(temp).printInfo();
            break;
        }
    }
}

void CliInterface::change_personal_information()
{
    while (true)
    {
        cout << "请输入要更改的用户的编号（从1开始，不超过用户总数）" << endl;
        int index = my_safe_read_int();
        index--; // 改为计算机习惯的数字
        if (index < 0 || index >= social_network.get_user_count())
        {
            cout << "数字越界，请重新输入" << endl;
        }
        else
        {
            while (true)
            {
                cout << "请输入要修改的信息" << endl;
                print_menu_choice<UserInfoChoice>(UserInfoChoice::ID, "ID");
                print_menu_choice<UserInfoChoice>(UserInfoChoice::Name, "姓名");
                print_menu_choice<UserInfoChoice>(UserInfoChoice::Sex, "性别");
                print_menu_choice<UserInfoChoice>(UserInfoChoice::Age, "年龄");
                print_menu_choice<UserInfoChoice>(UserInfoChoice::Job, "职业");

                int info = my_safe_read_int();
                if (info < 0 || info >= static_cast<int8_t>(UserInfoChoice::count_plus_one))
                {
                    cout << "数字无效，请重新输入" << endl;
                }
                else
                {
                    switch (static_cast<UserInfoChoice>(info))
                    {
                    case UserInfoChoice::ID:
                    {
                        social_network.set_user(index).setId(set_user_id_core());
                        break;
                    }
                    case UserInfoChoice::Name:
                    {
                        social_network.set_user(index).setName(set_user_name_core().getData());
                        break;
                    }
                    case UserInfoChoice::Sex:
                    {
                        social_network.set_user(index).setSex(set_user_sex_core());
                        break;
                    }
                    case UserInfoChoice::Age:
                    {
                        social_network.set_user(index).setAge(set_user_age_core());
                        break;
                    }
                    case UserInfoChoice::Job:
                    {
                        social_network.set_user(index).setJob(set_user_job_core().getData());
                        break;
                    }
                    default:
                    {
                        // 理论上不可达
                        cout << "数字无效，请重新输入" << endl;
                        break;
                    }
                    }
                    break;
                }
            }
            break;
        }
    }
}

void CliInterface::define_relationship_need_rebuild_connected()
{
    print_menu_choice<RelationshipDefMethod>(RelationshipDefMethod::SameAge, "同龄人");
    print_menu_choice<RelationshipDefMethod>(RelationshipDefMethod::AgeDifferenceWithin, "年龄差距在一定范围内的人");
    print_menu_choice<RelationshipDefMethod>(RelationshipDefMethod::SameSex, "同性别的人");
    print_menu_choice<RelationshipDefMethod>(RelationshipDefMethod::SameJob, "同职业的人");
    print_menu_choice<RelationshipDefMethod>(RelationshipDefMethod::Manually, "手动设置关系（支持删除已有关系，现在是唯一删除已有关系的方式）");

    int rela_def_mode;
    while (true)
    {
        rela_def_mode = my_safe_read_int();
        if (rela_def_mode < 1 || rela_def_mode >= static_cast<int8_t>(RelationshipDefMethod::count_plus_one))
        {
            cout << "选项无效，请重新输入" << endl;
        }
        else
        {
            // 需要在除了Manually模式之外所有模式进行权限调整 （Manually内之前已经耦合了权限调整选项）
            if (rela_def_mode != static_cast<int8_t>(RelationshipDefMethod::Manually))
            {
                social_network.neighbors_matrix_unprepared();
            }

            switch (static_cast<RelationshipDefMethod>(rela_def_mode))
            {
            case RelationshipDefMethod::SameAge:
            {
                social_network.build_relationship_according_to([this](int user_0, int user_1)
                                                               { return social_network.get_user(user_0).getAge() == social_network.get_user(user_1).getAge(); });
                break;
            }
            case RelationshipDefMethod::AgeDifferenceWithin:
            {
                int diff;
                cout << "请输入能接受的年龄差距（包括该数本身，因此可以为0，不能为负数）" << endl;
                while (true)
                {
                    diff = my_safe_read_int();
                    if (diff < 0)
                    {
                        cout << "无效数字，请重新输入" << endl;
                    }
                    else
                    {
                        break;
                    }
                }
                // 捕获this指针，该lambda表达式才能访问social_network
                social_network.build_relationship_according_to([this, diff](int user_0, int user_1)
                                                               { return diff >= (social_network.get_user(user_0).getAge() - social_network.get_user(user_1).getAge()); });
                break;
            }
            case RelationshipDefMethod::SameSex:
            {
                social_network.build_relationship_according_to([this](int user_0, int user_1)
                                                               { return social_network.get_user(user_0).getSex() == social_network.get_user(user_1).getSex(); });
                break;
            }
            case RelationshipDefMethod::SameJob:
            {
                social_network.build_relationship_according_to([this](int user_0, int user_1)
                                                               { return social_network.get_user(user_0).getJob_MyString() == social_network.get_user(user_1).getJob_MyString(); });
                break;
            }
            case RelationshipDefMethod::Manually:
            {
                change_single_relationship_core();
                break;
            }
            default:
            {
                // 理论上不可达
                cout << "选项无效，请重新输入" << endl;
                break;
            }
            }

            if (rela_def_mode != static_cast<int8_t>(RelationshipDefMethod::Manually))
            {
                social_network.neighbors_matrix_prepared();
            }
        }
    }
}

inline void CliInterface::change_single_relationship_core()
{
    while (true)
    {
        cout << "请输入第一个用户的编号（从1开始，不超过用户总数）" << endl;
        int index_0 = my_safe_read_int();
        index_0--; // 改为计算机习惯的数字
        if (index_0 < 0 || index_0 >= social_network.get_user_count())
        {
            cout << "数字越界，请重新输入" << endl;
        }
        else
        {
            while (true)
            {
                cout << "请输入第二个用户的编号（与第一个用户不同；从1开始，不超过用户总数）" << endl;
                int index_1 = my_safe_read_int();
                index_1--; // 改为计算机习惯的数字
                if (index_1 < 0 || index_1 >= social_network.get_user_count())
                {
                    cout << "数字越界，请重新输入" << endl;
                }
                else if (index_1 == index_0)
                {
                    cout << "两用户编号不同，请重新输入" << endl;
                }
                else
                {
                    int logic_value;
                    while (true)
                    {
                        cout << "请输入想要设置的逻辑关系（1或任何正数代表连接，0或任何负数代表不连接）" << endl;
                        logic_value = my_safe_read_int();
                        break;
                    }
                    // static_cast<bool>(int) 的行为：将所有正数转换为true，将0和所有负数转换为false
                    // 遵照操作规范
                    social_network.neighbors_matrix_unprepared(); // is_connected矩阵也跟着失效
                    social_network.change_single_relationship_with_check(index_0, index_1, static_cast<bool>(logic_value));
                    social_network.neighbors_matrix_prepared();
                }
            }
        }
    }
}

int CliInterface::set_user_id_core()
{
    cout << "请设置用户ID" << endl;
    int temp = my_safe_read_int();
    return temp;
}

MyString CliInterface::set_user_name_core()
{
    cout << "请设置用户姓名" << endl;
    MyString temp;
    cin >> temp;
    return temp;
}

Sex CliInterface::set_user_sex_core()
{
    while (true)
    {
        cout << "请设置用户性别（f代表女性，m代表男性）" << endl;
        char temp = static_cast<char>(my_safe_read_int());
        if (temp == 'f')
        {
            return Sex::FEMALE;
        }
        else if (temp == 'm')
        {
            return Sex::MALE;
        }
        else
        {
            cout << "输入无效，请重新输入（f代表女性，m代表男性）" << endl;
        }
    }
    return Sex::FEMALE; // 一般这一行不可达
}

int CliInterface::set_user_age_core()
{
    cout << "请设置用户年龄（可等于0，不可小于0）" << endl;
    int temp;
    while (true)
    {
        temp = my_safe_read_int();
        if (temp >= 0)
        {
            break;
        }
        else
        {
            cout << "数据无效，请重新设置用户年龄（可等于0，不可小于0）" << endl;
        }
    }
    return temp;
}

MyString CliInterface::set_user_job_core()
{
    cout << "请设置用户职业" << endl;
    MyString temp;
    cin >> temp;
    return temp;
}

template <typename enum_type>
inline void CliInterface::print_menu_choice(enum_type number, MyString content)
{
    cout << static_cast<int>(number) << ": " << content << endl;
}

int CliInterface::my_safe_read_int()
{
    int temp;
    while (true)
    {
        cin >> temp;
        if (cin.fail())
        {
            cin.clear(); // 清楚“出错”标志
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除缓冲区所有内容，直到遇见换行符
            cout << "输入非数字，请重新输入！" << endl;
        }
        else
        {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 仍旧清楚缓冲区，防止数字后面跟的非数字脏数据
            return temp;
        }
    }
}
