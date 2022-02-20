project(CppModule)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${build_bin_debug})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${build_bin_release})

include_directories(Include)

FILE (GLOB ALL_SOURCES "Src/*.cpp" "Src/*.c")
FILE (GLOB ALL_INCLUDES "Include/*.hpp" "Include/*.h")

SET(ROOT_PATH "${PROJECT_SOURCE_DIR}")
ADD_DEFINITIONS(-DROOTPATH=\"${ROOT_PATH}\")

add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})

target_link_libraries(${PROJECT_NAME} Engine)
target_link_libraries(${PROJECT_NAME} Lua)