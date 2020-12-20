add_library(ECS INTERFACE)
target_include_directories(ECS INTERFACE ${PROJECT_SOURCE_DIR})
target_sources(ECS INTERFACE component.h)