#include "MainGameScene.h"

#include "Engine/Game/Game.h"
#include "Engine/Utility/VectorUtils.h"
#include "Game/Assets/GameColors.h"
#include "Game/GameObjects/RigidBodies/Terrain/TerrainRB.h"

MainGameScene::MainGameScene()
{
	// ---- Moving entities
	const PhysicsProperties basicPhysicsProperties{ 7.1f, 0.5f };
	constexpr float rbObjectsXOrigin = 500.f;

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

	m_fallingCircleOrange = std::make_unique<FallingCircleRB>(defaultCircleShape, basicPhysicsProperties, sf::Vector2f(rbObjectsXOrigin, 0));
	m_fallingCircleRed = std::make_unique<FallingCircleRB>   (defaultCircleShape, basicPhysicsProperties, sf::Vector2f(rbObjectsXOrigin - 20, 200));
	m_fallingBoxOrange = std::make_unique<FallingBoxRB>      (defaultRectShape, basicPhysicsProperties, sf::Vector2f(rbObjectsXOrigin + 20, 100));
	m_fallingBoxRed = std::make_unique<FallingBoxRB>         (defaultRectShape, basicPhysicsProperties, sf::Vector2f(rbObjectsXOrigin + 40, 300), -20);

	m_fallingCircleOrange->setVelocity(PhysicsWorld::GRAVITY * 7.f);
	m_fallingCircleRed->setVelocity   (sf::Vector2f(0.f, 0.f));
	m_fallingBoxOrange->setVelocity	  (sf::Vector2f(0.f, 0.f));
	m_fallingBoxRed->setVelocity	  (sf::Vector2f(0.f, 0.f));

	// ---- Terrain and physics world
	const PhysicsProperties terrainPhysicsProperties{ 7.1f, 0.5f, true };
	m_terrain = std::make_unique<TerrainRB>(terrainPhysicsProperties);

	m_physicsWorld = std::make_unique<PhysicsWorld>();

	m_physicsWorld->addRigidBody(*m_fallingCircleOrange);
	m_physicsWorld->addRigidBody(*m_fallingCircleRed);
	m_physicsWorld->addRigidBody(*m_fallingBoxOrange);
	m_physicsWorld->addRigidBody(*m_fallingBoxRed);
	m_physicsWorld->addRigidBody(*m_terrain);

	// ---- Adding gameObjects in order
	addGameObjects(m_physicsWorld.get());
	addGameObjects(m_terrain.get());

	addGameObjects(m_fallingCircleOrange.get(), m_fallingCircleRed.get(), m_fallingBoxOrange.get(), m_fallingBoxRed.get());
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

	// ---- Debug shapes
	m_circleMousePos.setRadius(TERRAIN_DEBUG_MOUSE_RADIUS);
	m_circleMousePos.setFillColor(sf::Color(0, 255, 0, 100));
	m_circleMousePos.setOrigin(m_circleMousePos.getRadius(), m_circleMousePos.getRadius());

	m_blackHole.setRadius(60);
	m_blackHole.setPosition(windowSize.x / 2, 200);
	m_blackHole.setOrigin(m_blackHole.getRadius(), m_blackHole.getRadius());

	m_hitBlackHolePoint.setRadius(10);
	m_hitBlackHolePoint.setFillColor(sf::Color::Red);
	m_hitBlackHolePoint.setOrigin(m_hitBlackHolePoint.getRadius(), m_hitBlackHolePoint.getRadius());

	m_hitBlackHolePointRect.setSize(sf::Vector2f(15.f, 15.f));
	m_hitBlackHolePointRect.setFillColor(sf::Color::Red);
	m_hitBlackHolePointRect.setOrigin(m_hitBlackHolePointRect.getSize().x / 2.f, m_hitBlackHolePointRect.getSize().y / 2.f);

	// ---- Convex shapes
	m_convexShapeStatic.setPointCount(m_baseShape2.size());
	for (int i = 0; i < static_cast<int>(m_convexShapeStatic.getPointCount()); ++i)
		m_convexShapeStatic.setPoint(i, m_baseShape2[i]);

	m_convexShapeMousePos.setPointCount(m_baseShape1.size());
	for (int i = 0; i < static_cast<int>(m_convexShapeMousePos.getPointCount()); ++i)
		m_convexShapeMousePos.setPoint(i, m_baseShape1[i]);

	constexpr float CONVEX_SHAPES_SIZE = 20.f;

	m_convexShapeMousePos.setScale(CONVEX_SHAPES_SIZE, CONVEX_SHAPES_SIZE);
	m_convexShapeMousePos.setFillColor(GameColors::transparentBlack);
	m_convexShapeMousePos.setOutlineThickness(3 / CONVEX_SHAPES_SIZE);

	m_convexShapeStatic.setScale(CONVEX_SHAPES_SIZE, CONVEX_SHAPES_SIZE);
	m_convexShapeStatic.setFillColor(GameColors::dirty);
	m_convexShapeStatic.setPosition(300, 200);
}

void MainGameScene::update(const float& deltaTime)
{
	IScene::update(deltaTime);

	// ---- Terrain hit test
	m_circleMousePos.setPosition(static_cast<sf::Vector2f>(getMousePositionWindow()));

	// ---- Circle circle hit test
	CollisionUtils::HitResult ccHitResult;
	const bool hitCircleCircleDebug = CollisionUtils::circleToCircle(
		m_circleMousePos.getPosition(), m_circleMousePos.getRadius(), 
		m_blackHole.getPosition(), m_blackHole.getRadius(), 
		ccHitResult);

	m_blackHole.setFillColor(hitCircleCircleDebug ? GameColors::smoothPurple : GameColors::nightPurple);
	// m_hitBlackHolePoint.setPosition(ccHitResult.impactPoint);
	m_hitBlackHolePointRect.setPosition(ccHitResult.impactPoint);

	// ---- Polygons hit test
	m_convexShapeMousePos.setPosition(static_cast<sf::Vector2f>(getMousePositionWindow()));
	m_convexShapeMousePos.rotate(20.f * deltaTime);

	std::vector<sf::Vector2f> convexShapeEdgesStatic;
	for (const auto& edge : m_baseShape2)
		convexShapeEdgesStatic.emplace_back(m_convexShapeStatic.getTransform().transformPoint(edge));

	std::vector<sf::Vector2f> convexShapeEdgesMouse;
	for (const auto& edge : m_baseShape1)
		convexShapeEdgesMouse.emplace_back(m_convexShapeMousePos.getTransform().transformPoint(edge));

	CollisionUtils::HitResult ppHitResult;
	const bool hitPolyDebug = CollisionUtils::polygonToPolygon(convexShapeEdgesStatic, convexShapeEdgesMouse, ppHitResult);

	m_convexShapeMousePos.setOutlineColor(hitPolyDebug ? sf::Color::Blue : sf::Color(255, 0, 0, 150));

	// ---- Polygon - Circle hit test
	CollisionUtils::HitResult pcHitResult;
	const bool hitCirclePolyDebug = CollisionUtils::polygonToCircle(convexShapeEdgesStatic, m_circleMousePos.getPosition(), m_circleMousePos.getRadius(), pcHitResult);

	m_circleMousePos.setFillColor(hitCirclePolyDebug ? sf::Color::Blue : sf::Color(255, 0, 0, 150));

	if(ccHitResult.hasHit)
	{
		std::cout << VectorUtils::ToString(ccHitResult.normal) << std::endl;
	}
}

void MainGameScene::render()
{
	m_window.draw(m_background);

	IScene::render();

	m_window.draw(m_blackHole);
	m_window.draw(m_hitBlackHolePoint);
	m_window.draw(m_hitBlackHolePointRect);

	m_window.draw(m_convexShapeStatic);

	m_window.draw(m_convexShapeMousePos);
	m_window.draw(m_circleMousePos);
}
