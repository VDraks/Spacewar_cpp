
include_directories(${SDL2_INCLUDE_DIRS})
message("SDL2_INCLUDE_DIRS!!!" ${SDL2_INCLUDE_DIRS})
message("SDL2_LIBRARIES!!!" ${SDL2_LIBRARIES})

add_library(View main_view.cpp)
target_link_libraries(View SDL2::SDL2-static SDL2::SDL2main)

