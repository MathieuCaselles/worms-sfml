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
 "Physics/CollisionExternalDispatcher.h"
 "Physics/PhysicsWorld.h" "Physics/PhysicsWorld.cpp"

 "Physics/RigidBodies/IRigidBody.h"       "Physics/RigidBodies/IRigidBody.cpp"
 "Physics/RigidBodies/CircleRigidBody.h"  "Physics/RigidBodies/CircleRigidBody.cpp" 
 "Physics/RigidBodies/BoxRigidBody.h"     "Physics/RigidBodies/BoxRigidBody.cpp"
 "Physics/RigidBodies/TerrainRigidBody.h" "Physics/RigidBodies/TerrainRigidBody.cpp"

 "Components/GraphicsComponents/GCVoid.h" "Components/GraphicsComponents/GCVoid.cpp" "Components/GraphicsComponents/UI/Buttons/GCButton.h" "Components/GraphicsComponents/UI/Buttons/GCButton.cpp"
 "Components/InputComponents/ICVoid.h" "Components/InputComponents/ICVoid.cpp" "Components/InputComponents/UI/Buttons/ICButton.h" "Components/InputComponents/UI/Buttons/ICButton.cpp"
 "Components/PhysicsComponents/PCVoid.h" "Components/PhysicsComponents/PCVoid.cpp" "Components/PhysicsComponents/UI/Buttons/PCButton.h" "Components/PhysicsComponents/UI/Buttons/PCButton.cpp"
 "GameObjects/UI/Buttons/Button.h" "GameObjects/UI/Buttons/Button.cpp" "GameObjects/UI/HUD.h" "GameObjects/UI/Buttons/Button.cpp" "GameObjects/UI/HUD.cpp"

 "GameObjects/PhysicsObjects/Terrain/Terrain.h" "GameObjects/PhysicsObjects/Terrain/Terrain.cpp" 
 "GameObjects/PhysicsObjects/Terrain/GCTerrain.h" "GameObjects/PhysicsObjects/Terrain/GCTerrain.cpp" 
 "GameObjects/PhysicsObjects/Terrain/PCTerrain.h" "GameObjects/PhysicsObjects/Terrain/PCTerrain.cpp"
    
 "GameObjects/PhysicsObjects/BlackHole/BlackHole.h" "GameObjects/PhysicsObjects/BlackHole/BlackHole.cpp"
 "GameObjects/PhysicsObjects/BlackHole/PCBlackHole.h" "GameObjects/PhysicsObjects/BlackHole/PCBlackHole.cpp"
 "GameObjects/PhysicsObjects/BlackHole/GCBlackHole.h" "GameObjects/PhysicsObjects/BlackHole/GCBlackHole.cpp"

 "GameObjects/PhysicsObjects/ForceVolume/ForceVolume.h" "GameObjects/PhysicsObjects/ForceVolume/ForceVolume.cpp" 
 "GameObjects/PhysicsObjects/ForceVolume/PCForceVolume.h" "GameObjects/PhysicsObjects/ForceVolume/PCForceVolume.cpp"

 "GameObjects/Player/Player.h" "GameObjects/Player/Player.cpp" "GameObjects/Player/GCPlayer.h" "GameObjects/Player/GCPlayer.cpp"
 "GameObjects/Player/ICPlayer.h" "GameObjects/Player/ICPlayer.cpp" "GameObjects/Player/PCPlayer.h" "GameObjects/Player/PCPlayer.cpp"

 "GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h" "GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.cpp"
 "GameObjects/PhysicsObjects/Projectiles/Grenade/GCGrenade.h" "GameObjects/PhysicsObjects/Projectiles/Grenade/GCGrenade.cpp"
 "GameObjects/PhysicsObjects/Projectiles/Grenade/PCGrenade.h" "GameObjects/PhysicsObjects/Projectiles/Grenade/PCGrenade.cpp"

 "GameObjects/PhysicsObjects/Projectiles/FragmentationBall/FragmentationBall.h" "GameObjects/PhysicsObjects/Projectiles/FragmentationBall/FragmentationBall.cpp"
)