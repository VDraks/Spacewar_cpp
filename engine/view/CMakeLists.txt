
include_directories(${SDL2_INCLUDE_DIRS})

add_library(View main_view.cpp)
target_link_libraries(View Model SDL2::SDL2-static SDL2::SDL2main)

