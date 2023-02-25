#pragma once

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>

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
    std::unique_ptr<PhysicsWorld> m_physicsWorld;

    std::unique_ptr<Terrain> m_terrain;

    std::unique_ptr<FallingCircle> m_fallingCircleOrange1;
    std::unique_ptr<FallingCircle> m_fallingCircleOrange2;
    std::unique_ptr<FallingBox> m_fallingBoxOrange1;
    std::unique_ptr<FallingBox> m_fallingBoxOrange2;

    std::unique_ptr<ForceVolume> m_windForce;
    sf::Vector2f m_windDirection;

    // ---- Drawings
    sf::RectangleShape m_background;
};
