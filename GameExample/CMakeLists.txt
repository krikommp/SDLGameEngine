project(GameExample)

include_directories(Include)

FILE (GLOB ALL_SOURCES "Src/*.cpp" "Src/*.c")
FILE (GLOB ALL_INCLUDES "Include/*.hpp" "Include/*.h")

SET(ROOT_PATH "${PROJECT_SOURCE_DIR}")
ADD_DEFINITIONS(-DROOTPATH=\"${ROOT_PATH}\")

add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})
target_link_libraries(${PROJECT_NAME} SoftWareRenderer)

target_include_directories(${PROJECT_NAME} INTERFACE Include)