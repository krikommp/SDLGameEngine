project(TestGame)

# enable_testing()

include_directories(Include)

FILE (GLOB ALL_SOURCES "Src/*.cpp" "Src/*.c")
FILE (GLOB ALL_INCLUDES "Include/*.hpp" "Include/*.h")

add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2-static)
# target_link_libraries(${PROJECT_NAME} gtest_main)
# target_link_libraries(${PROJECT_NAME} Ubpa::UDRefl_core)

# include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME})