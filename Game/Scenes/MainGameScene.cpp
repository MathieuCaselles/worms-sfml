#include "MainGameScene.h"

#include "MainMenuScene.h"
#include "Engine/Game/Game.h"
#include "Engine/Utility/VectorUtils.h"
#include "Game/Assets/GameColors.h"

#include "Game/GameObjects/PhysicsObjects/FallingBox/FallingBox.h"
#include "Game/GameObjects/PhysicsObjects/FallingCircle/FallingCircle.h"
#include "Game/GameObjects/PhysicsObjects/Terrain/Terrain.h"
#include "Game/GameObjects/PhysicsObjects/ForceVolume/ForceVolume.h"
#include "Game/GameObjects/PhysicsObjects/BlackHole/BlackHole.h"

#include "Game/GameObjects/UI/HUD.h"


#include <utility>
#include <string>
#include <iostream>

#include "Engine/Utility/MathUtils.h"
#include "Game/GameObjects/Player/Player.h"

MainGameScene::MainGameScene()
{
	const PhysicsProperties basicPhysicsProperties{ 1.2f, 0.5f };
	const PhysicsProperties blackHolePhysicsProperties{ 1.f, 0, true, false, true};
	const PhysicsProperties playerPhysicsProperties{ 0.5f, 0.5f, false, false };
	const PhysicsProperties terrainPhysicsProperties{ 7.3f, .5f, true };

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

	auto fallingCircleOrange1 = Engine::GameObjectFactory::create<FallingCircle>(defaultCircleShape, basicPhysicsProperties, sf::Vector2f(920, 0));
	auto fallingCircleOrange2 = Engine::GameObjectFactory::create<FallingCircle>(defaultCircleShape, basicPhysicsProperties, sf::Vector2f(700, 100));
	auto wormPlayer1 = Engine::GameObjectFactory::create<Player>(100,playerShape, playerPhysicsProperties, sf::Vector2f(500, 100));
	auto wormPlayer2 = Engine::GameObjectFactory::create<Player>(100,playerShape, playerPhysicsProperties, sf::Vector2f(1300, 100));
	auto blackHole = Engine::GameObjectFactory::create<BlackHole>(blackHoleShape, blackHolePhysicsProperties, sf::Vector2f(800, 250), PhysicsWorld::GRAVITY_FORCE.y * 1.5);

	// ---- Terrain and physics world
	auto terrain = Engine::GameObjectFactory::create<Terrain>(terrainPhysicsProperties);
	m_wormPlayer1 = wormPlayer1.get();
	m_wormPlayer2 = wormPlayer2.get();
	m_physicsWorld.addRigidBody(*wormPlayer1);
	m_physicsWorld.addRigidBody(*wormPlayer2);
	m_physicsWorld.addRigidBody(*fallingCircleOrange1);
	m_physicsWorld.addRigidBody(*fallingCircleOrange2);
	//m_physicsWorld.addRigidBody(*blackHole);
	m_physicsWorld.addRigidBody(*terrain);

	// ---- Adding gameObjects in order
	addGameObjects(Engine::GameObjectFactory::create<ForceVolume>(m_physicsWorld.getAllRigidBodies(), VectorUtils::Rotate(sf::Vector2f(0, 200), 180*MathUtils::DEG_TO_RAD)));

	addGameObjects(std::move(terrain));
	//addGameObjects(std::move(blackHole));
	addGameObjects(std::move(fallingCircleOrange1), std::move(fallingCircleOrange2), std::move(wormPlayer1)
	, std::move(wormPlayer2));
	
	addGameObjects(Engine::GameObjectFactory::create<Button>(1700, 25, 200, 50, "Quitter", 30.f,
		sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) {m_window.close(); }));
}

void MainGameScene::onBeginPlay()
{
	IScene::onBeginPlay();
	initTitle();
	initInformations();
	initAllSounds();
	initTime();
	m_wormPlayer1->setCanPlay(true);
	m_currentPlayer = m_wormPlayer1;
	m_timeByTurn = 60;
	m_timeBetweenTransition = 3;
	m_rectSourceSprite = { 0, 0, 105, 155 };

	m_explosionFX.loadFromFile("Assets/Textures/VFXExplosion.png");

	m_spriteExplosionFX.setTexture(m_explosionFX);
	m_spriteExplosionFX.setTextureRect(m_rectSourceSprite);

	const auto windowSize = static_cast<sf::Vector2f>(m_window.getSize());

	// ---- Background
	initBackground();

	{

		// Exemple d'utilisation  de findGameObject attention à bien check si c'est pas nullptr en cas d'objet non trouvé !
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
void MainGameScene::initAllSounds()
{
	if (!m_ost.openFromFile("Assets/Musics/MapOST.wav"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD MUSIC");
	if (!m_shootSound.openFromFile("Assets/Musics/Shoot.wav"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD MUSIC");
	if (!m_explosionSound.openFromFile("Assets/Musics/Explosion.wav"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD MUSIC");
	if (!m_hitSound.openFromFile("Assets/Musics/Hit.wav"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD MUSIC");
	m_ost.setLoop(true);
	m_ost.play();
}

void MainGameScene::playExplosionSound()
{
	m_explosionSound.play();
}

void MainGameScene::playShootSound()
{
	m_shootSound.play();
}

void MainGameScene::playHitSound()
{
	m_hitSound.play();
}

void MainGameScene::playExplosionFX()
{
	if (clock.getElapsedTime().asSeconds() > 0.2f && canPlayExplosionFX) {
		if (m_rectSourceSprite.left == 400)
		{
			m_rectSourceSprite.left = 0;
			canPlayExplosionFX = false;
		}
		else if (m_rectSourceSprite.left == 100)
			m_rectSourceSprite.left += 150;
		else if (m_rectSourceSprite.left == 250)
			m_rectSourceSprite.left += 150;
		else
		{
			m_rectSourceSprite.left += 100;
			// TODO: detect coords of projectile
		}
		m_spriteExplosionFX.setTextureRect(m_rectSourceSprite);
		clock.restart();
	} else
	{
		m_spriteExplosionFX.setPosition(3000.f, 3000.f);
	}
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
		{
			m_wormPlayer1->setCanPlay(true);
		}
		else
		{
			m_wormPlayer2->setCanPlay(true);
		}
	}

	// ---- Display
	if (m_wormPlayer1->getCanPlay())
		m_timeLeft.setString("Temps Joueur 1: " + std::to_string(m_timeByTurn - m_elapsed));
	else if (m_wormPlayer2->getCanPlay())
		m_timeLeft.setString("Temps Joueur 2: " + std::to_string(m_timeByTurn - m_elapsed));
	else
		m_timeLeft.setString("Transition: " + std::to_string(m_timeBetweenTransition - m_elapsed));
}



void MainGameScene::update(const float& deltaTime)
{
	m_physicsWorld.step(deltaTime);
	updateTimeLeftForPlayers();
	playExplosionFX();

	IScene::update(deltaTime);

}

void MainGameScene::render()
{
	m_window.draw(m_background);
	m_window.draw(m_title);
	m_window.draw(m_wind);
	m_window.draw(m_timeLeft);
	m_window.draw(m_spriteExplosionFX);
	
	IScene::render();
}


