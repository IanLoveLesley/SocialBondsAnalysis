// created by corn on June 6, 2026

#pragma once
#include <iostream>

enum class Sex: char
{
    FEMALE = 0,
    MALE = 1,
};

// 输出结果是字符串"female"或者"male"。
// 不仅用enum class提高代码可读性，还需要在输出时确保输出结果的可读性
std::ostream& operator<<(std::ostream& out, const Sex& sex);