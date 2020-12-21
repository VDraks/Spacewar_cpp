find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(controller)

add_library(Engine engine.cpp)
target_link_libraries(Engine Model View Controller SDL2::Main)