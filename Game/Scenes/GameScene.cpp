#include "GameScene.h"
#include <Game/GameObjects/UI/Buttons/Button.h>
#include "Engine/Game/Game.h"

GameScene::GameScene()
{
	initBackground();
	initTitle();

	addGameObjects(new Button(50, 50, 200, 50, "Options", 30.f,
		sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) {m_window.close(); }));
}

GameScene::~GameScene()
{
	
}

void GameScene::processInput(sf::Event& inputEvent)
{
	if (inputEvent.key.code == sf::Keyboard::Escape)
		initAnnounce();

	IScene::processInput(inputEvent);
}

void GameScene::render()
{
	m_window.draw(m_background);
	m_window.draw(m_title);
	m_window.draw(m_announce);

	IScene::render();
}

void GameScene::initBackground()
{
	if (!m_backgroundTexture.loadFromFile("Assets/Textures/GameBackGround.jpg"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD TEXTURE");

	m_background.setPosition(0.f, 0.f);
	m_background.setSize({ 1920.f, 1080.f });
	m_background.setTexture(&m_backgroundTexture);
}

void GameScene::initTitle()
{
	if (!m_font.loadFromFile("Assets/Fonts/WormsFont.ttf")) {
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD FONT");
	}
	m_title.setFont(m_font);
	m_title.setString("Shoot and Destroy");
	m_title.setFillColor(sf::Color(40, 40, 40));
	m_title.setCharacterSize(35);
	m_title.setPosition(730, 500);
}

void GameScene::initAnnounce()
{
	if (!m_font.loadFromFile("Assets/Fonts/WormsFont.ttf")) {
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD FONT");
	}
	m_announce.setFont(m_font);
	m_announce.setString("Calvin couldn't take anymore !");
	m_announce.setFillColor(sf::Color(0, 0, 0));
	m_announce.setCharacterSize(20);
	m_announce.setPosition(700, 200);
}