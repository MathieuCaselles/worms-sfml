cmake_minimum_required(VERSION 3.25.2)

add_library(Engine)
add_library(Worms::Engine ALIAS Engine)


file(COPY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../_deps/sfml-src/extlibs/bin/x64/openal32.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

target_link_libraries(Engine PUBLIC
    project_options
    Worms::Tools
    sfml-graphics sfml-audio
)
target_include_directories(Engine PUBLIC
 $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../>
)

target_sources(Engine PRIVATE
  "Components/GraphicsComponent.h" "Components/InputComponent.h" "Components/PhysicsComponent.h"
  "Game/Game.h" "Game/Game.cpp"
  "GameObject/GameObject.h"
  "Scene/Scene.h" "Scene/Scene.cpp"
   "Utility/VectorUtils.h" "Utility/PolygonHelper.h" "Utility/MathUtils.h" "Utility/CollisionUtils.h")
