project(3rd)

set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory(SDL)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(googletest)

add_subdirectory(fmt)

add_subdirectory(Lua)

# add_subdirectory(UDRefl)