include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)


#find_package(SDL_ttf REQUIRED)
#include_directories(${SDL_TTF_INCLUDE_DIR})

add_library(View main_view.cpp)
target_link_libraries(View Model SDL2::Core SDL2::TTF)

