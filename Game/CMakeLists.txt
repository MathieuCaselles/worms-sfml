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

 "Scenes/SceneEnum.h" 
 "Scenes/MainMenuScene.h" "Scenes/MainMenuScene.cpp"
 "Scenes/MainGameScene.h" "Scenes/MainGameScene.cpp"

 "Physics/PhysicsProperties.h"
 "Physics/PhysicsWorld.h" "Physics/PhysicsWorld.cpp"
 "Physics/PCPhysicsWorld.h" "Physics/PCPhysicsWorld.cpp"  

 "Physics/IRigidBody.h" "Physics/IRigidBody.cpp"
 "Physics/RigidBodies/CircleRigidBody.h" "Physics/RigidBodies/CircleRigidBody.cpp" 
 "Physics/RigidBodies/BoxRigidBody.h" "Physics/RigidBodies/BoxRigidBody.cpp"

 "Components/GraphicsComponents/GCVoid.h" "Components/GraphicsComponents/GCVoid.cpp" "Components/GraphicsComponents/UI/Buttons/GCButton.h" "Components/GraphicsComponents/UI/Buttons/GCButton.cpp"
 "Components/InputComponents/ICVoid.h" "Components/InputComponents/ICVoid.cpp" "Components/InputComponents/UI/Buttons/ICButton.h" "Components/InputComponents/UI/Buttons/ICButton.cpp"
 "Components/PhysicsComponents/PCVoid.h" "Components/PhysicsComponents/PCVoid.cpp" "Components/PhysicsComponents/UI/Buttons/PCButton.h" "Components/PhysicsComponents/UI/Buttons/PCButton.cpp"
 "GameObjects/UI/Buttons/Button.h" "GameObjects/UI/Buttons/Button.cpp"

 "GameObjects/Terrain/Terrain.h" "GameObjects/Terrain/Terrain.cpp" 
 "GameObjects/Terrain/GCTerrain.h" "GameObjects/Terrain/GCTerrain.cpp" 
 "GameObjects/Terrain/PCTerrain.h" "GameObjects/Terrain/PCTerrain.cpp"

 "GameObjects/PhysicsObjects/FallingCircle/FallingCircleRB.h" "GameObjects/PhysicsObjects/FallingCircle/FallingCircleRB.cpp"
 "GameObjects/PhysicsObjects/FallingCircle/GCFallingCircle.h" "GameObjects/PhysicsObjects/FallingCircle/GCFallingCircle.cpp" 
 "GameObjects/PhysicsObjects/FallingCircle/PCFallingCircle.h" "GameObjects/PhysicsObjects/FallingCircle/PCFallingCircle.cpp"

 "GameObjects/PhysicsObjects/FallingBox/FallingBoxRB.h" "GameObjects/PhysicsObjects/FallingBox/FallingBoxRB.cpp"
 "GameObjects/PhysicsObjects/FallingBox/GCFallingBox.h" "GameObjects/PhysicsObjects/FallingBox/GCFallingbox.cpp"
 "GameObjects/PhysicsObjects/FallingBox/PCFallingBox.h" "GameObjects/PhysicsObjects/FallingBox/PCFallingBox.cpp")