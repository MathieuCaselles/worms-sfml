cmake_minimum_required(VERSION 3.25.2)

add_library(Engine)
add_library(Worms::Engine ALIAS Engine)
target_link_libraries(Engine PUBLIC
    project_options
    sfml-graphics sfml-audio sfml-system
)
target_include_directories(Engine PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)

target_sources(Engine PRIVATE
  test.cpp
  test.h)
