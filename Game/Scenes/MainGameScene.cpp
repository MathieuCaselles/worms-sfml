#include "MainGameScene.h"

#include "Engine/Game/Game.h"
#include "Engine/Utility/VectorUtils.h"
#include "Game/Assets/GameColors.h"

#include "Game/GameObjects/PhysicsObjects/FallingBox/FallingBox.h"
#include "Game/GameObjects/PhysicsObjects/FallingCircle/FallingCircle.h"
#include "Game/GameObjects/PhysicsObjects/Terrain/Terrain.h"
#include "Game/GameObjects/PhysicsObjects/ForceVolume/ForceVolume.h"


#include <utility>

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

	auto m_fallingCircleOrange1 = Engine::GameObjectFactory::create<FallingCircle>(defaultCircleShape, basicPhysicsProperties, sf::Vector2f(900, 0));
	auto m_fallingCircleOrange2 = Engine::GameObjectFactory::create<FallingCircle>(defaultCircleShape, basicPhysicsProperties, sf::Vector2f(520, 300));
	auto m_fallingBoxOrange1    = Engine::GameObjectFactory::create<FallingBox>(defaultRectShape, playerPhysicsProperties, sf::Vector2f(200, 400), 0);
	auto m_fallingBoxOrange2    = Engine::GameObjectFactory::create<FallingBox>(defaultRectShape, basicPhysicsProperties, sf::Vector2f(820, 500), -20);
	m_fallingBoxOrange2->setAngularVelocity(60);

	// ---- Terrain and physics world
	auto m_terrain = Engine::GameObjectFactory::create<Terrain>(terrainPhysicsProperties);

	m_physicsWorld.addRigidBody(*m_fallingCircleOrange1);
	m_physicsWorld.addRigidBody(*m_fallingCircleOrange2);
	m_physicsWorld.addRigidBody(*m_fallingBoxOrange1);
	m_physicsWorld.addRigidBody(*m_fallingBoxOrange2);
	m_physicsWorld.addRigidBody(*m_terrain);

	// ---- Volumes


	// ---- Adding gameObjects in order
		// ---- Volumes
	addGameObjects(Engine::GameObjectFactory::create<ForceVolume>(
		m_physicsWorld.getAllRigidBodies(),
		VectorUtils::Rotate(sf::Vector2f(-60, 0), 30)
	));
	addGameObjects(std::move(m_terrain));

	addGameObjects(std::move(m_fallingCircleOrange1), std::move(m_fallingCircleOrange2), std::move(m_fallingBoxOrange1), std::move(m_fallingBoxOrange2));
}

void MainGameScene::onBeginPlay()
{
	IScene::onBeginPlay();

	const auto windowSize = static_cast<sf::Vector2f>(m_window.getSize());

	// ---- Background
	m_background.setSize(windowSize);
	m_background.setFillColor(GameColors::sky);
}

void MainGameScene::update(const float& deltaTime)
{
	m_physicsWorld.step(deltaTime);

	IScene::update(deltaTime);
}

void MainGameScene::render()
{
	m_window.draw(m_background);

	IScene::render();
}
