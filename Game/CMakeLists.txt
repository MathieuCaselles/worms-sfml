cmake_minimum_required(VERSION 3.25.2)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


add_executable(Worms)
target_link_libraries(Worms PUBLIC
    project_options
    Worms::Engine
)
target_include_directories(Worms PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)

target_sources(Worms PRIVATE
  main.cpp
)
