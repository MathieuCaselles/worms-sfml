#pragma once

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class MainMenuScene : public Engine::IScene
{
public:

    MainMenuScene();
    ~MainMenuScene();

     void processInput(sf::Event& inputEvent) override;
     void render() override;

     void onBeginPlay() override;
     void onEndPlay() override;


private:

    void initBackground();
    void initTitle();
    void initOst();






    sf::Text m_title;
    sf::Font m_font;

    sf::Texture m_backgroundTexture;
    sf::RectangleShape m_background;

    sf::Music m_ost;

};