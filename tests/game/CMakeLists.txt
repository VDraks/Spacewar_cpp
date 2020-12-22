file(GLOB_RECURSE Game_test_SRC CONFIGURE_DEPENDS "*.cpp")
add_executable(Game_test ${Game_test_SRC})
target_link_libraries(Game_test Game gtest_main)