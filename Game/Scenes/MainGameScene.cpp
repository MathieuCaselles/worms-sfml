#include "MainGameScene.h"

#include "MainMenuScene.h"
#include "Engine/Game/Game.h"
#include "Engine/Utility/VectorUtils.h"
#include "Game/Assets/GameColors.h"

#include "Game/GameObjects/PhysicsObjects/FallingBox/FallingBox.h"
#include "Game/GameObjects/PhysicsObjects/FallingCircle/FallingCircle.h"
#include "Game/GameObjects/PhysicsObjects/Terrain/Terrain.h"
#include "Game/GameObjects/PhysicsObjects/ForceVolume/ForceVolume.h"
#include "Game/GameObjects/UI/Buttons/Options.h"
#include "Game/GameObjects/UI/HUD.h"

#include "Game/Physics/PhysicsWorld.h"

MainGameScene::MainGameScene()
{
	const PhysicsProperties basicPhysicsProperties{ 1.2f, 0.5f };
	const PhysicsProperties playerPhysicsProperties{ 4.0f, 0.5f, false, false };
	const PhysicsProperties terrainPhysicsProperties{ 7.3f, .5f, true };

	// ---- Entities
	sf::CircleShape defaultCircleShape;
	defaultCircleShape.setRadius(20);
	defaultCircleShape.setOrigin(defaultCircleShape.getRadius(), defaultCircleShape.getRadius());
	defaultCircleShape.setFillColor(GameColors::orange);
	defaultCircleShape.setOutlineColor(sf::Color::Black);
	defaultCircleShape.setOutlineThickness(1);

	sf::RectangleShape defaultRectShape;
	defaultRectShape.setSize(sf::Vector2f(40.f, 40.f));
	defaultRectShape.setOrigin(defaultRectShape.getSize().x / 2.f, defaultRectShape.getSize().y / 2.f);
	defaultRectShape.setFillColor(GameColors::orange);
	defaultRectShape.setOutlineColor(sf::Color::Black);
	defaultRectShape.setOutlineThickness(1);

	//m_hud = std::make_unique<HUD>();

	m_fallingCircleOrange1 = std::make_unique<FallingCircle>(defaultCircleShape, basicPhysicsProperties, sf::Vector2f(900, 0));
	m_fallingCircleOrange2 = std::make_unique<FallingCircle>(defaultCircleShape, basicPhysicsProperties, sf::Vector2f(520, 300));
	m_fallingBoxOrange1    = std::make_unique<FallingBox>(defaultRectShape, playerPhysicsProperties, sf::Vector2f(200, 400), 0);
	m_fallingBoxOrange2    = std::make_unique<FallingBox>(defaultRectShape, basicPhysicsProperties, sf::Vector2f(820, 500), -20);
	m_fallingBoxOrange2->setAngularVelocity(60);

	// ---- Terrain and physics world
	m_terrain = std::make_unique<Terrain>(terrainPhysicsProperties);

	m_physicsWorld = std::make_unique<PhysicsWorld>();
	m_physicsWorld->addRigidBody(*m_fallingCircleOrange1);
	m_physicsWorld->addRigidBody(*m_fallingCircleOrange2);
	m_physicsWorld->addRigidBody(*m_fallingBoxOrange1);
	m_physicsWorld->addRigidBody(*m_fallingBoxOrange2);
	m_physicsWorld->addRigidBody(*m_terrain);

	// ---- Volumes
	m_windForce = std::make_unique<ForceVolume>(m_physicsWorld->getAllRigidBodies());
	m_windForce->setForce(VectorUtils::Rotate(sf::Vector2f(-60, 0), 30));


	// ---- Adding gameObjects in order
	
	addGameObjects(m_windForce.get());
	addGameObjects(m_terrain.get());

	addGameObjects(m_fallingCircleOrange1.get(), m_fallingCircleOrange2.get(), m_fallingBoxOrange1.get(), m_fallingBoxOrange2.get());
	addGameObjects(new Options(1700, 25, 200, 50, "Options", 30.f,
		sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) {m_window.close(); }));
	
}

void MainGameScene::onBeginPlay()
{
	initTitle();
	initInformations();
	initOst();

	const auto windowSize = static_cast<sf::Vector2f>(m_window.getSize());
	m_hud->SetButtonOptions();

	// ---- Background
	initBackground();

	// ---- Terrain
	m_terrain->generateTerrain(windowSize);
}

void MainGameScene::initTitle()
{
	if (!m_font.loadFromFile("Assets/Fonts/WormsFont.ttf")) {
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD FONT");
	}
	m_title.setFont(m_font);
	m_title.setString("Shoot and Destroy");
	m_title.setFillColor(sf::Color(40, 40, 40));
	m_title.setCharacterSize(35);
	m_title.setPosition(730, 350);
}

void MainGameScene::initInformations()
{
	if (!m_font.loadFromFile("Assets/Fonts/WormsFont.ttf")) {
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD FONT");
	}

	m_wind.setFont(m_font);
	m_wind.setString("Wind: " + std::to_string(m_windForce->getForce().y));
	m_wind.setFillColor(sf::Color(255, 255, 255));
	m_wind.setCharacterSize(20);
	m_wind.setPosition(80, 25);
}

void MainGameScene::initBackground()
{
	if (!m_backgroundTexture.loadFromFile("Assets/Textures/GameBackGround.jpg"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD TEXTURE");

	m_background.setSize({ 1920.f, 1080.f });
	m_background.setTexture(&m_backgroundTexture);
}

void MainGameScene::update(const float& deltaTime)
{
	m_physicsWorld->step(deltaTime);

	IScene::update(deltaTime);
}

void MainGameScene::render()
{

	m_window.draw(m_background);
	m_window.draw(m_title);
	m_window.draw(m_wind);

	IScene::render();
}

void MainGameScene::initOst()
{
	if (!m_ost.openFromFile("Assets/Musics/MainMenuOST.wav"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD MUSIC");
	m_ost.setLoop(true);
	m_ost.play();
}