project(Lua)

FILE (GLOB ALL_SOURCES "Src/*.cpp" "Src/*.c")
FILE (GLOB ALL_INCLUDES "Src/*.hpp" "Src/*.h")

add_library(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})
target_include_directories(${PROJECT_NAME} INTERFACE Src)