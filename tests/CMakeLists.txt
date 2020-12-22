add_compile_definitions(GTEST_LANG_CXX11=1)
add_subdirectory(googletest-1.7.0)

include_directories(SYSTEM ${gtest_SOURCE_DIR}/include)

add_subdirectory(engine)
add_subdirectory(game)