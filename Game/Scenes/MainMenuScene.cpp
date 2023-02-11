#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
{
	if (!m_font.loadFromFile("Assets/Fonts/WormsFont.ttf")) {
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD FONT");
	}


	if (!m_backgroundTexture.loadFromFile("Assets/Textures/BackgroundWorms.jpg"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD TEXTURE");

	m_background.setPosition(0.f, 0.f);
	m_background.setSize({1920.f, 1080.f});
	m_background.setTexture(&m_backgroundTexture);

	//init font
	m_title.setFont(m_font);
	m_title.setString("Worms SFML EDITION");
	m_title.setFillColor(sf::Color(252, 79, 36));
	m_title.setCharacterSize(60);
	m_title.setPosition(300, 150);

	//init music

	//if (!m_ost.openFromFile("Assets/Musics/MainMenuOST.wav"))
	//	throw("ERROR::MAINMENUSCENE::COULD NOT LOAD MUSIC");

	//m_ost.setLoop(true);

}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::render()
{
	IScene::render();

	m_window.draw(m_background);
	m_window.draw(m_title);
}
