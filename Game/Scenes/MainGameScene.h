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
	void render() override;

private:
    sf::RectangleShape _background;

    std::unique_ptr<Terrain> _terrain;
};
