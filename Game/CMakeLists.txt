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
 "Scenes/SceneEnum.h" "Scenes/MainMenuScene.h" "Scenes/MainMenuScene.cpp"
 "Components/GraphicsComponents/GCVoid.h" "Components/GraphicsComponents/GCVoid.cpp" "Components/GraphicsComponents/UI/Buttons/GCButton.h" "Components/GraphicsComponents/UI/Buttons/GCButton.cpp"
 "Components/InputComponents/ICVoid.h" "Components/InputComponents/ICVoid.cpp" "Components/InputComponents/UI/Buttons/ICButton.h" "Components/InputComponents/UI/Buttons/ICButton.cpp"
 "Components/PhysicsComponents/PCVoid.h" "Components/PhysicsComponents/PCVoid.cpp" "Components/PhysicsComponents/UI/Buttons/PCButton.h" "Components/PhysicsComponents/UI/Buttons/PCButton.cpp"
 "GameObjects/UI/Buttons/Button.h" "GameObjects/UI/Buttons/Button.cpp"

)
