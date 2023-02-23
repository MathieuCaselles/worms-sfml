#include "MainGameScene.h"

#include "Engine/Game/Game.h"
#include "Engine/Utility/VectorUtils.h"
#include "Game/Assets/GameColors.h"

#include "Game/GameObjects/PhysicsObjects/FallingBox/FallingBox.h"
#include "Game/GameObjects/PhysicsObjects/FallingCircle/FallingCircle.h"
#include "Game/GameObjects/PhysicsObjects/Terrain/Terrain.h"
#include "Game/GameObjects/PhysicsObjects/ForceVolume/ForceVolume.h"

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

	m_fallingCircleOrange1 = std::make_unique<FallingCircle>(defaultCircleShape, basicPhysicsProperties, sf::Vector2f(900, 0));
	m_fallingCircleOrange2    = std::make_unique<FallingCircle>(defaultCircleShape, basicPhysicsProperties, sf::Vector2f(520, 300));
	m_fallingBoxOrange1    = std::make_unique<FallingBox>(defaultRectShape, playerPhysicsProperties, sf::Vector2f(200, 400), 0);
	m_fallingBoxOrange2       = std::make_unique<FallingBox>(defaultRectShape, basicPhysicsProperties, sf::Vector2f(820, 500), -20);

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
	m_windForce->setForce(VectorUtils::Rotate(sf::Vector2f(-60, 0), 0));

	// ---- Adding gameObjects in order
	addGameObjects(m_windForce.get());
	addGameObjects(m_terrain.get());

	addGameObjects(m_fallingCircleOrange1.get(), m_fallingCircleOrange2.get(), m_fallingBoxOrange1.get(), m_fallingBoxOrange2.get());
}

void MainGameScene::onBeginPlay()
{
	IScene::onBeginPlay();

	const auto windowSize = static_cast<sf::Vector2f>(m_window.getSize());

	// ---- Background
	m_background.setSize(windowSize);
	m_background.setFillColor(GameColors::sky);

	// ---- Terrain
	m_terrain->generateTerrain(windowSize);
}

void MainGameScene::update(const float& deltaTime)
{
	m_physicsWorld->step(deltaTime);

	IScene::update(deltaTime);
}

void MainGameScene::render()
{
	m_window.draw(m_background);

	IScene::render();
}
