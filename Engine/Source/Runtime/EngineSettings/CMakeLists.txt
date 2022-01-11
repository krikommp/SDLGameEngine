project(EngineSettings)

include_directories(Public Classes)

FILE (GLOB ALL_SOURCES
        "*.cpp" "*.c"
        "Private/*.cpp" "Private/*.c"
        "Classes/*.cpp" "Classes/*.c"
        )

FILE (GLOB ALL_INCLUDES
        "*.hpp" "*.h"
        "Private/*.hpp" "Private/*.h"
        "Public/*.h" "Public/*.hpp"
        "Classes/*.h" "Classes/*.hpp"
        )

add_library(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})

target_include_directories(${PROJECT_NAME} INTERFACE Public Classes)
