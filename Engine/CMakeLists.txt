Project(BreakGameEngine)
cmake_minimum_required(VERSION 3.14)

if (MSVC)
    # 设置 msvc 输入代码编码格式为 utf-8
    set(CMAKE_C_FLAGS /source-charset:utf-8)
endif()

add_subdirectory(Source)