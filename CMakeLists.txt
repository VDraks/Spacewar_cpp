cmake_minimum_required(VERSION 3.17)
project(Spacewar)

add_subdirectory(engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Spacewar main.cpp)
target_link_libraries(Spacewar Engine)