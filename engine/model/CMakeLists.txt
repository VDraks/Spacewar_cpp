file(GLOB_RECURSE Model_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
add_library(Model ${Model_SRC})

