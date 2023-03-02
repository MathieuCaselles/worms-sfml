#pragma once

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>

#include "SFML/Audio/Music.hpp"

class FragmentationBall;
class Grenade;
class PhysicsWorld;
class Player;
class Button;

class MainGameScene : public Engine::IScene
{
public:
    MainGameScene();
    ~MainGameScene() override = default;

    void onBeginPlay() override;
    void update(const float& deltaTime) override;
	void render() override;

    Player* getCurrentPlayer();

    const bool isChangeTurn() const;

    void spawnGrenade(const sf::Vector2f& position, const sf::Vector2f& direction);
    void spawnFragBall(const sf::Vector2f& position, const sf::Vector2f& direction);
    void spawnBlackHole(const  sf::Vector2f& position);

    void unselectPreviousButton();

    void updateButtonsSKillInfo();

    bool m_hasPlayed = false;

    void playShootSound();
    void playExplosionSound();
    void playHitSound();

private:
    void initBackground();
    void initInformations();
    void initTitle();
    void initAllSounds();
    void initTime();

    void printPlayerToPlay();

    void updateTimeLeftForPlayers();
    void makeTransition();

    // ---- Grenade
    Grenade* m_grenade;
    FragmentationBall* m_fragBall;

    // ---- Drawings
    sf::RectangleShape m_background;

    // ---- Players
	Player* m_wormPlayer1;
    Player* m_wormPlayer2;
    Player* m_currentPlayer;

    // ---- Buttons

    Button* m_buttonGrenade;
    Button* m_buttonFragBall;
    Button* m_buttonBlackHole;

    // ---- Game

    sf::Text m_title;
    sf::Text m_wind;
    sf::Text m_timeLeft;
    sf::Font m_font;

    sf::Music m_ost;
    sf::Music m_explosionSound;
    sf::Music m_shootSound;
    sf::Music m_hitSound;

    sf::Clock m_clock;
    int m_elapsed;

    bool m_changeTurn = false;
    int m_timeByTurn;
    int m_timeBetweenTransition;

    sf::Texture m_backgroundTexture;
    sf::Texture m_textureCalvin;
    
};
