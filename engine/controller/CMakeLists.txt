file(GLOB_RECURSE Controller_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
add_library(Controller ${Controller_SRC})
target_link_libraries(Controller SDL2::Core)