add_library(Model world.cpp game_object.cpp)

message("CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

