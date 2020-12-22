include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)

file(GLOB_RECURSE View_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
add_library(View ${View_SRC})
target_link_libraries(View Model SDL2::Core SDL2::TTF)

