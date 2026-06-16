#include "..\include\CliInterface.h"
constexpr int MIN_USERS = 10;

CliInterface::CliInterface() : social_network(initialize_user_count()) {}

void CliInterface::run()
{
    bool is_running = true; // 通过设置这个状态参数为false来终止实例化的进程运行
    initialize_users();
    define_relationship();
    social_network.build_is_connected_matrix();

    while (is_running)
    {
        MenuChoice choice = get_user_menu_choice();
        switch (choice)
        {
        case MenuChoice::Quit:
        {
            cout << "感谢使用，再见" << endl;
            is_running = false;
            break;
        }
        case MenuChoice::PrintConnectedMatrix:
        {
            print_is_connected_matrix();
            break;
        }
        // case MenuChoice::ShowDiagram: { break; }
        case MenuChoice::ChangePersonalInformation:
        {
            change_personal_information();
            break;
        }
        case MenuChoice::ChangeRelationship:
        {
            change_relationship_need_rebuild_connected();
            social_network.build_is_connected_matrix();
            break;
        }
        // case MenuChoice::AddUser: { break; }
        // case MenuChoice::DeleteUser: { break; }
        default:
        {
            cout << "选项无效，请重新输入" << endl;
            break;
        }
        }
    }
}

// 这个函数属于整个类而非其中某个具体的对象
// 通过它与Cli界面类的构造函数的组合间接实现 social_network 的初始化
// 由于底层数据结构限制，一个进程内暂时无法改变用户数量（但可以随意改换每一个节点的信息以及项链关系）
int CliInterface::initialize_user_count()
{
    int temp;
    cout << "初始化：请输入社交网络用户个数（大于等于" << MIN_USERS << ")" << endl;

    while (true)
    {
        cin >> temp;
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

void CliInterface::define_relationship()
{
    // TODO
    // 主要是输入邻接矩阵的规则，可能需要扩展更多规则
    social_network.neighbors_matrix_prepared(); // 最后要做的事情：使矩阵准备好
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
        cout << i+1 << '\t';
        for (int j = 0; j < user_count; j++)
        {
            cout << source.get_element(i,j) << '\t';
        }
        cout << endl;
    }
}

CliInterface::MenuChoice CliInterface::get_user_menu_choice()
{
    
}

int CliInterface::set_user_id_core()
{
    cout << "请设置用户id" << endl;
    int temp;
    cin >> temp;
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
        char temp;
        cin >> temp;
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
        cin >> temp;
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

inline void CliInterface::print_menu_choice(MenuChoice number, MyString target)
{
    cout << static_cast<int>(number) << ": " << target << endl;
}
