file(GLOB_RECURSE Game_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

include_directories(${PROJECT_SOURCE_DIR})

add_library(Game ${Game_SRC} systems/player_controller_system.cpp systems/player_controller_system.h components/player.h)
target_link_libraries(Game Engine)