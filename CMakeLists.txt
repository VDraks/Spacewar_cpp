cmake_minimum_required(VERSION 3.7)
project(Spacewar)

set(CMAKE_CXX_STANDARD 17)

message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/engine)

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(tests)


add_executable(Spacewar main.cpp)
target_link_libraries(Spacewar Game)