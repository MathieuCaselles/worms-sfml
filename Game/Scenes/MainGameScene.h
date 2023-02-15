#pragma once

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

    sf::RectangleShape m_background;

    // ---- Debug shapes
    sf::CircleShape m_mousePosCircle;

    std::unique_ptr<Terrain> m_terrain;
};
