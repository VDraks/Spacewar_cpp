cmake_minimum_required(VERSION 3.10)
project(Spacewar)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

set(CMAKE_CXX_STANDARD 17)



message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/engine)

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(tests)


add_executable(Spacewar main.cpp)
target_link_libraries(Spacewar Game)

if(MSVC)
    target_compile_options(Spacewar PUBLIC /W4 /WX)
else()
    target_compile_options(Spacewar PUBLIC -Wall -Wextra -pedantic -Werror)
endif()