#pragma once

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>

#include "Game/GameObjects/RigidBodies/FallingBox/FallingBoxRB.h"
#include "Game/GameObjects/RigidBodies/FallingCircle/FallingCircleRB.h"
#include "Game/GameObjects/RigidBodies/Terrain/TerrainRB.h"

#include "Game/Physics/PhysicsWorld.h"

class MainGameScene : public Engine::IScene
{
public:
    MainGameScene();
    ~MainGameScene() override = default;

    void onBeginPlay() override;
    void update(const float& deltaTime) override;
	void render() override;

private:
    std::unique_ptr<PhysicsWorld> m_physicsWorld;
    std::unique_ptr<FallingCircleRB> m_fallingCircleOrange;
    std::unique_ptr<FallingCircleRB> m_fallingCircleRed;
    std::unique_ptr<FallingBoxRB> m_fallingBoxOrange;
    std::unique_ptr<FallingBoxRB> m_fallingBoxRed;

    sf::RectangleShape m_background;
    std::unique_ptr<TerrainRB> m_terrain;

    // ---- Debug shapes
    sf::CircleShape m_circleMousePos;

    sf::CircleShape m_blackHole;
    sf::CircleShape m_hitBlackHolePoint;
    sf::RectangleShape m_hitBlackHolePointRect;

    sf::ConvexShape m_convexShapeStatic;
    sf::ConvexShape m_convexShapeMousePos;

    const std::vector<sf::Vector2f> m_baseShape1
    {
        sf::Vector2f(0, 2),
        sf::Vector2f(2, 1),
        sf::Vector2f(2, -1),
        sf::Vector2f(0, -2),
        sf::Vector2f(-2, -2),
        sf::Vector2f(-2, -1)
    };

    const std::vector<sf::Vector2f> m_baseShape2
    {
        sf::Vector2f(1, 3),
        sf::Vector2f(2, 2),
        sf::Vector2f(2, -1),
        sf::Vector2f(-1, -3),
        sf::Vector2f(-2, -1),
        sf::Vector2f(-2, 0)
    };
};
