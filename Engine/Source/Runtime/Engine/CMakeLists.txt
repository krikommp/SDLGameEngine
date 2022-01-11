project(Engine)

include_directories(Classes Public)

FILE (GLOB ALL_SOURCES 
"Private/*.cpp" "Private/*.c" 
"Private/Components/*.c" "Private/Components/*.cpp"
"Private/Engine/*.c" "Private/Engine/*.cpp"
)

FILE (GLOB ALL_INCLUDES 
"Private/*.hpp" "Private/*.h" 
"Classes/*.h" "Classes/*.hpp" 
"Public/*.h" "Public/*.hpp" 
"Private/Components/*.h" "Private/Components/*.hpp"
"Classes/Components/*.h" "Classes/Components/*.hpp"
"Private/Engine/*.h" "Private/Engine/*.hpp"
"Classes/Engine/*.h" "Classes/Engine/*.hpp"
) 

add_library(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})
target_link_libraries(${PROJECT_NAME} Core EngineSettings)

target_include_directories(${PROJECT_NAME} INTERFACE Classes Public)
