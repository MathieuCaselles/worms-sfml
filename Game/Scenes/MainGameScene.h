#pragma once

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>

#include "SFML/Audio/Music.hpp"

class Grenade;
class PhysicsWorld;

class MainGameScene : public Engine::IScene
{
public:
    MainGameScene();
    ~MainGameScene() override = default;

    void onBeginPlay() override;
    void update(const float& deltaTime) override;
	void render() override;

    void spawnGrenade(const sf::Vector2f& position, const sf::Vector2f& direction);

private:
    void initBackground();
    void initInformations();
    void initTitle();
    void initOst();

    // ---- Grenade
    Grenade* m_grenade;

    // ---- Drawings
    sf::RectangleShape m_background;

    sf::Text m_title;
    sf::Text m_wind;
    sf::Font m_font;

    sf::Music m_ost;

    sf::Texture m_backgroundTexture;
    sf::Texture m_textureCalvin;
};
