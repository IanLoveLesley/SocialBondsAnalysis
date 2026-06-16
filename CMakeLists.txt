# 设置 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.20)

# 定义项目名称
project(SocialNetworkAnalysis)

# 强制使用 C++11 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定字符集为 UTF-8 ，防止乱码
add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)

# 指定头文件的搜索目录
include_directories(include)

# 🛠️ 使用 file(GLOB ...) 自动将 src 目录下所有的 .cpp 文件收集到 SOURCES 变量中
file(GLOB SOURCES "src/*.cpp")

# 生成最终的可执行文件
add_executable(SocialNetworkAnalysis ${SOURCES})