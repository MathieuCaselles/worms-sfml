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
class Player;

class MainGameScene : public Engine::IScene
{
public:
    MainGameScene();
    ~MainGameScene() override = default;

    void onBeginPlay() override;
    void update(const float& deltaTime) override;
	void render() override;

private:
    void initBackground();
    void initInformations();
    void initTitle();
    void initOst();
    void initTime();
    void updateTimeLeft();

    // ---- System
    PhysicsWorld m_physicsWorld;

    // ---- Drawings
    sf::RectangleShape m_background;

    // ---- Players
	Player* m_wormPlayer1;
    Player* m_wormPlayer2;

    sf::Text m_title;
    sf::Text m_wind;
    sf::Text m_timeLeft;
    sf::Font m_font;

    sf::Music m_ost;

    sf::Clock m_clock;
    sf::Time m_elapsed;

    sf::Texture m_backgroundTexture;
    sf::Texture m_textureCalvin;
};
