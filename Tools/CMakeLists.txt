cmake_minimum_required(VERSION 3.25.2)

add_library(Tools)
add_library(Worms::Tools ALIAS Tools)
target_link_libraries(Tools PUBLIC
    project_options
)
target_include_directories(Tools PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)

target_sources(Tools PRIVATE
   "MathUtils.h" "MathUtils.cpp"
   "DesignPatterns/Composite.h" "DesignPatterns/Singleton.h"
 "DesignPatterns/Factory.h" "Typelist.h")
