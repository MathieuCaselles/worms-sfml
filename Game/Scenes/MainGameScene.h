#pragma once

#include <array>

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>

#include "Game/GameObjects/Terrain/Terrain.h"


class MainGameScene : public Engine::IScene
{
public:
    MainGameScene();
    ~MainGameScene() override = default;

    void onBeginPlay() override;
    void update(const float& deltaTime) override;
	void render() override;

private:
    void updateSkyColor(const sf::Color& color);

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

    const std::vector<sf::Vector2f> m_baseShape3
    {
        sf::Vector2f(40, 40),
        sf::Vector2f(40, -40),
        sf::Vector2f(-40, -40),
        sf::Vector2f(-40, 40)
    };

    sf::RectangleShape m_background;
    sf::CircleShape m_blackHole;
    sf::CircleShape m_hitBlackHolePoint;

    sf::ConvexShape m_convexShapeStatic;
    sf::ConvexShape m_convexShapeMousePos;

    // ---- Debug shapes
    sf::CircleShape m_circleMousePos;

    std::unique_ptr<Terrain> m_terrain;
};
