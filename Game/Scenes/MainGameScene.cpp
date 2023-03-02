#include "MainGameScene.h"

#include "MainMenuScene.h"
#include "Engine/Game/Game.h"
#include "Game/Assets/GameColors.h"

#include "Game/GameObjects/PhysicsObjects/Terrain/Terrain.h"
#include "Game/GameObjects/PhysicsObjects/BlackHole/BlackHole.h"
#include "Game/GameObjects/UI/Buttons/Button.h"

#include <utility>
#include <string>
#include <iostream>

#include "Game/GameObjects/PhysicsObjects/Projectiles/FragmentationBall/FragmentationBall.h"
#include "Game/GameObjects/Player/Player.h"

constexpr int PLAYER_HEALTH = 100;

MainGameScene::MainGameScene() : m_currentPlayer(nullptr), m_grenade(nullptr), m_fragBall(nullptr)
{
	
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

	auto wormPlayer1 = Engine::GameObjectFactory::create<Player>(PLAYER_HEALTH, playerShape, playerPhysicsProperties, sf::Vector2f(500, 100));
	auto wormPlayer2 = Engine::GameObjectFactory::create<Player>(PLAYER_HEALTH,playerShape, playerPhysicsProperties, sf::Vector2f(1300, 100));
	m_wormPlayer1 = wormPlayer1.get();
	m_wormPlayer2 = wormPlayer2.get();


	// ---- Terrain and physics world
	auto terrain = Engine::GameObjectFactory::create<Terrain>(terrainPhysicsProperties);

	m_physicsWorld.addRigidBody(*m_wormPlayer1);
	m_physicsWorld.addRigidBody(*m_wormPlayer2);
	m_physicsWorld.addRigidBody(*m_grenade);
	m_physicsWorld.addRigidBody(*m_fragBall);
	m_physicsWorld.addRigidBody(*terrain);

	// ---- Adding gameObjects in order
	addGameObjects(std::move(terrain));
	addGameObjects(std::move(wormPlayer1));
	addGameObjects(std::move(wormPlayer2));
	addGameObjects(std::move(grenade));
	addGameObjects(std::move(fragBall));




	addGameObjects(Engine::GameObjectFactory::create<Button>(1700, 25, 200, 50, "Options", 30.f,
		sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) {m_window.close(); }));


	auto grenadeButton = Engine::GameObjectFactory::create<Button>(350, 25, 325, 50, "->Grenade", 30.f,
				sf::Color(225, 0, 0), sf::Color(255, 0, 0), sf::Color(195, 0, 0),
				[&](Button* button) {
					if (m_changeTurn)
						return;
					m_currentPlayer->setSkillState(GRENADE);
					updateButtonsSKillInfo();
				},
				[&](Button* button) {
					if (m_changeTurn)
						return;
					m_currentPlayer->setCanPlay(false);
				}
						,
				[&](Button* button) {
				if (m_changeTurn)
					return;
				m_currentPlayer->setCanPlay(true);
			}
		);

	auto fragBallButton = Engine::GameObjectFactory::create<Button>(700, 25, 325, 50, "Banane (x1)", 30.f,
		sf::Color(156, 181, 44), sf::Color(186, 201, 74), sf::Color(126, 151, 14),
		[&](Button* button) {
			if (m_changeTurn || m_currentPlayer->getNumberBanana() <= 0)
				return;
			m_currentPlayer->setSkillState(BANANA);
			updateButtonsSKillInfo();
		},
		[&](Button* button) {
			if (m_changeTurn)
				return;
			m_currentPlayer->setCanPlay(false);
		}
			,
			[&](Button* button) {
			if (m_changeTurn)
				return;
			m_currentPlayer->setCanPlay(true);
		});

	auto blackHoleButton = Engine::GameObjectFactory::create<Button>(1050, 25, 325, 50, "Trou noir (x1)", 30.f,
		sf::Color(30, 30, 30), sf::Color(60, 60, 60), sf::Color(0, 0, 0),
		[&](Button* button) {
			if (m_changeTurn || m_currentPlayer->getNumberBlackHole() <= 0)
				return;
			m_currentPlayer->setSkillState(BLACK_HOLE);
			updateButtonsSKillInfo();
		},
		[&](Button* button) {
			if (m_changeTurn)
				return;
			m_currentPlayer->setCanPlay(false);
		},
			[&](Button* button) {
			if (m_changeTurn)
				return;
			m_currentPlayer->setCanPlay(true);
		});


	m_buttonGrenade = grenadeButton.get();
	m_buttonFragBall = fragBallButton.get();
	m_buttonBlackHole = blackHoleButton.get();

	addGameObjects(std::move(grenadeButton));
	addGameObjects(std::move(fragBallButton));
	addGameObjects(std::move(blackHoleButton));
}

void MainGameScene::onBeginPlay()
{
	IScene::onBeginPlay();
	initTitle();
	initInformations();
	initOst();
	initTime();
	m_wormPlayer1->setCanPlay(true);
	m_currentPlayer = m_wormPlayer1;
	m_timeByTurn = 60;
	m_timeBetweenTransition = 3;

	const auto windowSize = static_cast<sf::Vector2f>(m_window.getSize());

	// ---- Background
	initBackground();

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
	m_wind.setString("Vent:		TODO");
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
	m_grenade->shot(position, direction * m_fragBall->getLaunchForce());
	updateButtonsSKillInfo();
	m_hasPlayed = true;
}

void MainGameScene::spawnFragBall(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	m_fragBall->shot(position, direction * m_fragBall->getLaunchForce());
	updateButtonsSKillInfo();
	if (m_currentPlayer->getNumberBanana() == 0)
		m_currentPlayer->setSkillState(GRENADE);
	m_hasPlayed = true;

}

void MainGameScene::spawnBlackHole(const  sf::Vector2f& position)
{
	const PhysicsProperties blackHolePhysicsProperties{ 1.f, 0, true, false, true };
	sf::CircleShape blackHoleShape(150, 40);
	blackHoleShape.setOrigin(blackHoleShape.getRadius(), blackHoleShape.getRadius());
	blackHoleShape.setFillColor(sf::Color(GameColors::nightPurple.r, GameColors::nightPurple.g, GameColors::nightPurple.b, 100));
	blackHoleShape.setOutlineColor(GameColors::nightPurple);
	blackHoleShape.setOutlineThickness(6);

	auto blackHole = Engine::GameObjectFactory::create<BlackHole>(blackHoleShape, blackHolePhysicsProperties, position, PhysicsWorld::GRAVITY_FORCE.y * 1);
	m_physicsWorld.addRigidBody(*blackHole);
	addNewGameObjects(std::move(blackHole));
	updateButtonsSKillInfo();
	if (m_currentPlayer->getNumberBlackHole() == 0)
		m_currentPlayer->setSkillState(GRENADE);
	m_hasPlayed = true;

}

void MainGameScene::unselectPreviousButton()
{

	Button* previousSelected = static_cast<Button*>(
		findGameObject([](const Engine::IGameObject* gameObj) {
				if(gameObj->getInstanceRTTI() != Button::getClassRTTI())
					return false;
				return static_cast<const Button*>(gameObj)->getText().getString().substring(0, 2) == "->";
			})
		);
	if (previousSelected != nullptr)
		previousSelected->setText(previousSelected->getText().getString().substring(2, previousSelected->getText().getString().getSize()));

}

void MainGameScene::updateButtonsSKillInfo()
{
	unselectPreviousButton();

	m_buttonGrenade->setText((m_currentPlayer->getSkillState() == GRENADE ? "->" : "") + m_buttonGrenade->getText().getString());

	const std::string bananaTextButton = m_buttonFragBall->getText().getString().substring(0, m_buttonFragBall->getText().getString().getSize() - 2);
	m_buttonFragBall->setText((m_currentPlayer->getSkillState() == BANANA ? "->" : "") + bananaTextButton + std::to_string(m_currentPlayer->getNumberBanana()) + ")");

	const std::string blackTextHoleButton = m_buttonBlackHole->getText().getString().substring(0, m_buttonBlackHole->getText().getString().getSize() - 2);
	m_buttonBlackHole->setText((m_currentPlayer->getSkillState() == BLACK_HOLE ? "->" : "") + blackTextHoleButton + std::to_string(m_currentPlayer->getNumberBlackHole()) + ")");


}

void MainGameScene::initTime()
{
	m_timeLeft.setFont(m_font);
	m_timeLeft.setString("Temps: " + std::to_string(static_cast<int>(round(m_clock.getElapsedTime().asSeconds()))));
	m_timeLeft.setFillColor(sf::Color(255, 255, 255));
	m_timeLeft.setCharacterSize(30);
	m_timeLeft.setPosition(80, 150);
}

void MainGameScene::printPlayerToPlay()
{
	if (m_elapsed < m_timeBetweenTransition && m_changeTurn)
	{
		if (m_currentPlayer == m_wormPlayer1)
		{
			m_title.setString("Joueur 2 Préparez vous !");
		}
		else
		{
			m_title.setString("Joueur 1 Préparez vous !");
		}
	} else
	{
		m_title.setString("");
	}
}

void MainGameScene::updateTimeLeftForPlayers()
{
	m_elapsed = static_cast<int>(round(m_clock.getElapsedTime().asSeconds()));
	if (m_elapsed >= m_timeByTurn || m_hasPlayed)
	{
		m_wormPlayer1->setCanPlay(false);
		m_wormPlayer2->setCanPlay(false);
		m_changeTurn = true;
		m_hasPlayed = false;
		m_clock.restart();
	}
	makeTransition();
	printPlayerToPlay();
}

void MainGameScene::makeTransition()
{

	m_elapsed = static_cast<int>(round(m_clock.getElapsedTime().asSeconds()));
	if (m_elapsed >= m_timeBetweenTransition && m_changeTurn)
	{
		m_currentPlayer = (m_currentPlayer == m_wormPlayer1) ? m_wormPlayer2 : m_wormPlayer1;
		m_changeTurn = false;
		m_clock.restart();

		if (m_currentPlayer == m_wormPlayer1)
			m_wormPlayer1->setCanPlay(true);
		else
			m_wormPlayer2->setCanPlay(true);

		updateButtonsSKillInfo();
	}

	// ---- Display
	if (m_changeTurn)
		m_timeLeft.setString("Transition: " + std::to_string(m_timeBetweenTransition - m_elapsed));
	else if (m_currentPlayer == m_wormPlayer1)
		m_timeLeft.setString("Temps Joueur 1: " + std::to_string(m_timeByTurn - m_elapsed));
	else if (m_currentPlayer == m_wormPlayer2)
		m_timeLeft.setString("Temps Joueur 2: " + std::to_string(m_timeByTurn - m_elapsed));
	
}

void MainGameScene::update(const float& deltaTime)
{
	IScene::update(deltaTime);

	updateTimeLeftForPlayers();
}

void MainGameScene::render()
{
	m_window.draw(m_background);
	m_window.draw(m_title);
	m_window.draw(m_wind);
	m_window.draw(m_timeLeft);
	
	IScene::render();
}

Player* MainGameScene::getCurrentPlayer()
{
	return m_currentPlayer;
}

const bool MainGameScene::isChangeTurn() const
{
	return m_changeTurn;
}


