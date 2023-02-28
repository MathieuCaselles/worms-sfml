#pragma once

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>
#include "Game/Physics/PhysicsWorld.h"

#include "SFML/Audio/Music.hpp"

class BlackHole;
class ForceVolume;
class PhysicsWorld;
class Terrain;
class FallingBox;
class FallingCircle;
class HUD;

class MainGameScene : public Engine::IScene
{
public:
    MainGameScene();
    ~MainGameScene() override = default;

    void onBeginPlay() override;
    void update(const float& deltaTime) override;
	void render() override;
    PhysicsWorld& getPhysics();

private:
    void initBackground();
    void initInformations();
    void initTitle();
    void initOst();

    // ---- System
    PhysicsWorld m_physicsWorld;

    // ---- Drawings
    sf::RectangleShape m_background;

    sf::Text m_title;
    sf::Text m_wind;
    sf::Font m_font;

    sf::Music m_ost;

    sf::Texture m_backgroundTexture;
    sf::Texture m_textureCalvin;
};
