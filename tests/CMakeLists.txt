add_subdirectory(googletest-1.7.0)

include_directories(SYSTEM ${gtest_SOURCE_DIR}/include)

add_subdirectory(engine)