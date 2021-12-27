project(Engine)

include_directories(Classes)

FILE (GLOB ALL_SOURCES "Private/*.cpp" "Private/*.c")
FILE (GLOB ALL_INCLUDES "Private/*.hpp" "Private/*.h" "Classes/*.h" "Classes/*.hpp" "Public/*.h" "Public/*.hpp")

add_library(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})

target_include_directories(${PROJECT_NAME} INTERFACE Classes)
