file(GLOB_RECURSE ECS_TEST_SRC "*.cpp")
add_executable(Ecs_test ${ECS_TEST_SRC})
target_link_libraries(Ecs_test gtest_main)
#target_link_libraries(Ecs_test INTERFACE ECS)

