project(Launch)

include_directories(Public)

FILE (GLOB ALL_SOURCES
        "Private/*.cpp"
        "Private/*.c"
        "Private/Math/*.cpp"
        "Private/Math/*.c"
        )

FILE (GLOB ALL_INCLUDES
        "Private/*.hpp" "Private/*.h"
        "Public/*.h" "Public/*.hpp"
        "Private/Math/*.h" "Private/Math/*.hpp"
        "Public/Math/*.h" "Public/Math/*.hpp"
        )

add_library(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})
target_link_libraries(${PROJECT_NAME} Engine)

target_include_directories(${PROJECT_NAME} INTERFACE Public)
