cmake_minimum_required(VERSION 3.14)
project(SDLGameEngine)

set(CMAKE_BUILD_TYPE  "Debug")

if ( CMAKE_SYSTEM_NAME MATCHES "Windows" )
    set (my_std_pre "/std:")
else()
    set (my_std_pre "-std=")
endif()

set (basic_cxx20 "c++latest")
set (str_cxx20 "${my_std_pre}${basic_cxx20}")

include (CheckCXXCompilerFlag)
check_cxx_compiler_flag( "${str_cxx20}" _cpp_20_flag_supported )
if ( _cpp_20_flag_supported )
    set( CMAKE_CXX_STANDARD 20 )
else()
    set( CMAKE_CXX_STANDARD 17 )
endif()
if ( CMAKE_SYSTEM_NAME MATCHES "Windows" )
    # 设置 msvc 输入代码编码格式为 utf-8
    set(CMAKE_C_FLAGS /source-charset:utf-8)
endif()

if (CMAKE_CL_64)
    # 设置可执行程序输出目录
    set(build_bin_debug ${CMAKE_CURRENT_SOURCE_DIR}/build/x64/bin/debug64)
    set(build_bin_release ${CMAKE_CURRENT_SOURCE_DIR}/build/x64/bin/release64)

    # 设置库文件输出目录
    set(build_lib_debug ${CMAKE_CURRENT_SOURCE_DIR}/build/x64/lib/debug64)
    set(build_lib_release ${CMAKE_CURRENT_SOURCE_DIR}/build/x64/lib/release64)
else()
    # 设置可执行程序输出目录
    set(build_bin_debug ${CMAKE_CURRENT_SOURCE_DIR}/build/x86/bin/debug)
    set(build_bin_release ${CMAKE_CURRENT_SOURCE_DIR}/build/x86/bin/release)

    # 设置库文件输出目录
    set(build_lib_debug ${CMAKE_CURRENT_SOURCE_DIR}/build/x86/lib/debug)
    set(build_lib_release ${CMAKE_CURRENT_SOURCE_DIR}/build/x86/lib/release)
endif()

add_definitions(/wd"4819" /wd"4996" /wd"4800")

add_subdirectory(3rdparty)
add_subdirectory(Engine)
add_subdirectory(SDLGameEngine)
# Test Module
add_subdirectory(GameExample)

add_subdirectory(SandBox)
