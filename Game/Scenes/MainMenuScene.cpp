#include "MainMenuScene.h"
#include <Game/GameObjects/UI/Buttons/Button.h>

#include "SceneEnum.h"
#include "Engine/Game/Game.h"

MainMenuScene::MainMenuScene()
{
	initBackground();
	initOst();
	initTitle();

	addGameObjects(Engine::GameObjectFactory::create<Button>(1400, 400, 230, 80, "Jouer", 40.f,
		sf::Color(252, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) {
			Engine::Game* game = Engine::GameInstance::GetInstance();
			game->setCurrentScene(ScenesEnum::MAIN_GAME);
		}
	));
	addGameObjects(Engine::GameObjectFactory::create<Button>(1400, 600, 230, 80, "Quitter", 40.f,
		sf::Color(252, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) { m_window.close(); }
	));

}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::processInput(sf::Event& inputEvent)
{
	if (inputEvent.key.code == sf::Keyboard::Escape)
		m_window.close();

	IScene::processInput(inputEvent);
}

void MainMenuScene::render()
{
	m_window.draw(m_background);
	m_window.draw(m_title);

	IScene::render();
}

void MainMenuScene::onBeginPlay()
{
	m_ost.setLoop(true);
	m_ost.play();
}

void MainMenuScene::onEndPlay()
{
	m_ost.stop();
}

void MainMenuScene::initBackground()
{
	if (!m_backgroundTexture.loadFromFile("Assets/Textures/BackgroundWorms.jpg"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD TEXTURE");

	m_background.setPosition(0.f, 0.f);
	m_background.setSize({ 1920.f, 1080.f });
	m_background.setTexture(&m_backgroundTexture);
}

void MainMenuScene::initTitle()
{
	if (!m_font.loadFromFile("Assets/Fonts/WormsFont.ttf")) {
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD FONT");
	}
	m_title.setFont(m_font);
	m_title.setString("Worms SFML");
	m_title.setFillColor(sf::Color(252, 79, 36));
	m_title.setCharacterSize(80);
	m_title.setPosition(320, 150);
}

void MainMenuScene::initOst()
{
	if (!m_ost.openFromFile("Assets/Musics/OST_MainMenu.wav"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD MUSIC");

	m_ost.setVolume(m_ost.getVolume() / 3);
}
