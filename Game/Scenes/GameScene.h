#pragma once

#include <Engine/Scene/Scene.h>
#include <SFML/Graphics.hpp>

class GameScene : public Engine::IScene
{
public:
	GameScene();
	~GameScene();

	virtual void processInput(sf::Event& inputEvent) override;
	virtual void render() override;
private:

	void initBackground();
	void initAnnounce();
	void initTitle();

	sf::Text m_title;
	sf::Text m_announce;
	sf::Font m_font;

	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;
};