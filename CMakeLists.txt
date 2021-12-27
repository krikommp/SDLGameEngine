cmake_minimum_required(VERSION 3.14)
project(TestInClion)

if ( CMAKE_SYSTEM_NAME MATCHES "Windows" )
    set (my_std_pre "/std:")
else()
    set (my_std_pre "-std=")
endif()

set (basic_cxx20 "c++20")
set (str_cxx20 "${my_std_pre}${basic_cxx20}")

include (CheckCXXCompilerFlag)
check_cxx_compiler_flag( "${str_cxx20}" _cpp_20_flag_supported )
if ( _cpp_20_flag_supported )
    set( CMAKE_CXX_STANDARD 20 )
else()
    set( CMAKE_CXX_STANDARD 17 )    
endif()

if (MSVC)
    # 设置 msvc 输入代码编码格式为 utf-8
    set(CMAKE_C_FLAGS /source-charset:utf-8)
endif()

add_subdirectory(3rdparty)
add_subdirectory(Engine)

# Test Module
add_subdirectory(UnitTest)
