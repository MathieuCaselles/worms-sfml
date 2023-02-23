#pragma once

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>

#include "Game/GameObjects/PhysicsObjects/ForceVolume/ForceVolume.h"

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
    std::unique_ptr<PhysicsWorld> m_physicsWorld;

    std::unique_ptr<Terrain> m_terrain;

    std::unique_ptr<FallingCircle> m_fallingCircleOrange;
    std::unique_ptr<FallingCircle> m_fallingCircleRed;
    std::unique_ptr<FallingBox> m_fallingBoxOrange;
    std::unique_ptr<FallingBox> m_fallingBoxRed;

    std::unique_ptr<ForceVolume> m_windForce;
    sf::Vector2f m_windDirection;

    // ---- Drawings
    sf::RectangleShape m_background;
};
