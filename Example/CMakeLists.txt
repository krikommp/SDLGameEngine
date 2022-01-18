project(Example)

# enable_testing()

FILE (GLOB ALL_SOURCES "*.cpp" "*.c")
FILE (GLOB ALL_INCLUDES "*.hpp" "*.h")

add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})
# target_link_libraries(${PROJECT_NAME} SDL2main SDL2-static)
# target_link_libraries(${PROJECT_NAME} gtest_main)
target_link_libraries(${PROJECT_NAME} Engine)
target_link_libraries(${PROJECT_NAME} Lua)
# target_link_libraries(${PROJECT_NAME} Ubpa::UDRefl_core)

# include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME})