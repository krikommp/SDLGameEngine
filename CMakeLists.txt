cmake_minimum_required(VERSION 3.14)
project(TestInClion)

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
endif()

add_subdirectory(3rdparty)
add_subdirectory(UnitTest)
add_subdirectory(Engine)
