project(SoftWareRenderer)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${build_lib_debug})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${build_lib_release})

include_directories(Include)

FILE (GLOB ALL_SOURCES "Src/*.cpp" "Src/*.c")
FILE (GLOB ALL_INCLUDES "Include/*.hpp" "Include/*.h")

add_library(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2-static)
target_link_libraries(${PROJECT_NAME} fmt)

target_include_directories(${PROJECT_NAME} INTERFACE Include)