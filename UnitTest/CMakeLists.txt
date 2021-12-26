project(UnitTest)
FILE (GLOB ALL_SOURCES "*.cpp" "*.c")
FILE (GLOB ALL_INCLUDES "*.hpp" "*.h")

add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2-static)