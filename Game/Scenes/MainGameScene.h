#pragma once

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>
#include "Game/Physics/PhysicsWorld.h"

class ForceVolume;
class PhysicsWorld;
class Terrain;
class FallingBox;
class FallingCircle;

class MainGameScene : public Engine::IScene
{
public:
    MainGameScene();
    ~MainGameScene() override = default;

    void onBeginPlay() override;
    void update(const float& deltaTime) override;
	void render() override;

private:
    // ---- System
    PhysicsWorld m_physicsWorld;

    sf::Vector2f m_windDirection;

    // ---- Drawings
    sf::RectangleShape m_background;
};
