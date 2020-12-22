file(GLOB_RECURSE Game_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

include_directories(${PROJECT_SOURCE_DIR})

add_library(Game ${Game_SRC})
target_link_libraries(Game Engine)
target_include_directories(Game PUBLIC ${PROJECT_SOURCE_DIR})