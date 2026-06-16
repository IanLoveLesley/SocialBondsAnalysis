#include "../include/CliInterface.h"
#include <windows.h>

int main()
{
    // Windows 系统下设置编码方式为 UTF-8 （而不是默认的GBK）
    SetConsoleOutputCP(CP_UTF8);

    CliInterface CLI_interface;
    CLI_interface.run();
    return 0;
}