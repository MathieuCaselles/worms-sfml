#include "MainGameScene.h"

#include "MainMenuScene.h"
#include "Engine/Game/Game.h"
#include "Game/Assets/GameColors.h"

#include "Game/GameObjects/PhysicsObjects/Terrain/Terrain.h"
#include "Game/GameObjects/PhysicsObjects/BlackHole/BlackHole.h"

#include "Game/GameObjects/UI/HUD.h"

#include <utility>
#include <string>
#include <iostream>

#include "Game/GameObjects/PhysicsObjects/Projectiles/FragmentationBall/FragmentationBall.h"
#include "Game/GameObjects/Player/Player.h"

MainGameScene::MainGameScene()
{
	const PhysicsProperties blackHolePhysicsProperties{ 1.f, 0, true, false, true};
	const PhysicsProperties playerPhysicsProperties{ 0.5f, 0.5f, false, false };
	const PhysicsProperties terrainPhysicsProperties{ 7.3f, .5f, true };
	const PhysicsProperties grenadePhysicsProperties(4.f, 0.3f);
	const PhysicsProperties fragBallPhysicsProperties(1.5f, 0.8f);

	if (!m_textureCalvin.loadFromFile("Assets/Textures/calvin.png"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD TEXTURE");

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
	defaultCircleShape.setFillColor(GameColors::orange);
	defaultRectShape.setOutlineColor(sf::Color::Black);
	defaultRectShape.setOutlineThickness(1);

	sf::CircleShape playerShape;
	playerShape.setRadius(40);
	playerShape.setOrigin(playerShape.getRadius(), playerShape.getRadius());
	playerShape.setTexture(&m_textureCalvin);

	sf::CircleShape blackHoleShape(150, 40);
	blackHoleShape.setOrigin(blackHoleShape.getRadius(), blackHoleShape.getRadius());
	blackHoleShape.setFillColor(sf::Color(GameColors::nightPurple.r, GameColors::nightPurple.g, GameColors::nightPurple.b, 100));
	blackHoleShape.setOutlineColor(GameColors::nightPurple);
	blackHoleShape.setOutlineThickness(6);

	sf::CircleShape grenadeShape(15);
	grenadeShape.setFillColor(GameColors::iron);
	grenadeShape.setOutlineColor(sf::Color::Black);
	grenadeShape.setOutlineThickness(2);
	grenadeShape.setOrigin(grenadeShape.getRadius(), grenadeShape.getRadius());

	sf::CircleShape fragBallShape(12);
	fragBallShape.setFillColor(GameColors::banana);
	fragBallShape.setOutlineColor(sf::Color::Black);
	fragBallShape.setOutlineThickness(1);
	fragBallShape.setOrigin(fragBallShape.getRadius(), fragBallShape.getRadius());

	auto grenade = Engine::GameObjectFactory::create<Grenade>(grenadeShape, grenadePhysicsProperties);
	grenade->setLaunchForce(14.f);
	grenade->setDamages(15.f);
	m_grenade = grenade.get();

	auto fragBall = 
		Engine::GameObjectFactory::create<FragmentationBall>(fragBallShape, fragBallPhysicsProperties, 15);
	fragBall->setLaunchForce(9.f);
	fragBall->setDamages(10.f);
	fragBall->setFragmentsForceMinMax(7.f, 12.f);
	fragBall->setFragmentsDamage(3.f);
	fragBall->setFragmentsDurationBeforeExplosion(4.f);
	fragBall->setFragsSpawnXAngleIncertitude(15);
	m_fragBall = fragBall.get();

	auto wormPlayer1 = Engine::GameObjectFactory::create<Player>(playerShape, playerPhysicsProperties, sf::Vector2f(500, 100));
	auto blackHole = Engine::GameObjectFactory::create<BlackHole>(blackHoleShape, blackHolePhysicsProperties, sf::Vector2f(20, 20), PhysicsWorld::GRAVITY_FORCE.y * 1);

	// ---- Terrain and physics world
	auto terrain = Engine::GameObjectFactory::create<Terrain>(terrainPhysicsProperties);

	m_physicsWorld.addRigidBody(*wormPlayer1);
	m_physicsWorld.addRigidBody(*m_grenade);
	m_physicsWorld.addRigidBody(*m_fragBall);
	m_physicsWorld.addRigidBody(*blackHole);
	m_physicsWorld.addRigidBody(*terrain);

	// ---- Adding gameObjects in order
	addGameObjects(std::move(terrain));
	addGameObjects(std::move(blackHole));
	addGameObjects(std::move(wormPlayer1));
	addGameObjects(std::move(grenade));
	addGameObjects(std::move(fragBall));

	addGameObjects(Engine::GameObjectFactory::create<Button>(1700, 25, 200, 50, "Options", 30.f,
		sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) {m_window.close(); }));
}

void MainGameScene::onBeginPlay()
{
	IScene::onBeginPlay();
	initTitle();
	initInformations();
	initOst();

	const auto windowSize = static_cast<sf::Vector2f>(m_window.getSize());

	// ---- Background
	initBackground();


	{

		// Exemple d'utilisation  de findGameObject attention � bien check si c'est pas nullptr en cas d'objet non trouv� !
		const Button* go = static_cast<Button*>(
			findGameObject([](const Engine::IGameObject* gameObj) {
				return 	gameObj->getInstanceRTTI() == Button::getClassRTTI();
				})
			);

		std::cout << static_cast<std::string>(go->getText().getString()) << std::endl;

	}
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
	//m_wind.setString("Wind: " + std::to_string(m_windForce->getForce().y));
	m_wind.setString("Wind:		TODO");
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
void MainGameScene::initOst()
{
	//if (!m_ost.openFromFile("Assets/Musics/MainMenuOST.wav"))
	//	throw("ERROR::MAINMENUSCENE::COULD NOT LOAD MUSIC");
	//m_ost.setLoop(true);
	//m_ost.play();
}

void MainGameScene::spawnGrenade(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	m_fragBall->shot(position, direction * m_fragBall->getLaunchForce());
}

void MainGameScene::update(const float& deltaTime)
{
	IScene::update(deltaTime);
}

void MainGameScene::render()
{
	m_window.draw(m_background);
	m_window.draw(m_title);
	m_window.draw(m_wind);

	IScene::render();
}


