# 设置 CMake 的最低版本要求，通常 CLion 默认生成的版本就可以
cmake_minimum_required(VERSION 3.20)

# 定义项目名称
project(SocialNetworkAnalysis)

# 强制使用 C++11 标准（足够支持我们手搓的基础特性）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定头文件的搜索目录
# 这样你在 src 下的 cpp 文件里就可以直接写 #include "Person.h"
# 而不需要写相对路径 #include "../include/Person.h"
include_directories(include)

# 将所有的源文件 (.cpp) 汇总到一个变量 SOURCES 中
# 注意：MyVector.h 和 MyQueue.h 是模板类，声明和实现都写在头文件里，所以不需要写在这里
set(SOURCES
        src/main.cpp
        src/MyString.cpp
        src/Person.cpp
        src/SocialNetwork.cpp
)

# 生成最终的可执行文件
add_executable(SocialNetworkAnalysis ${SOURCES})