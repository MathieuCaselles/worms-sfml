#include "MainGameScene.h"

#include "Engine/Game/Game.h"
#include "Game/Assets/GameColors.h"
#include "Game/GameObjects/Terrain/Terrain.h"

MainGameScene::MainGameScene()
{
	m_terrain = std::make_unique<Terrain>();
	addGameObjects(m_terrain.get());
}

void MainGameScene::onBeginPlay()
{
	IScene::onBeginPlay();

	const auto windowSize = static_cast<sf::Vector2f>(m_window.getSize());

	m_background.setSize(windowSize);

	m_circleMousePos.setRadius(TERRAIN_DEBUG_MOUSE_RADIUS);
	m_circleMousePos.setFillColor(sf::Color(0, 255, 0, 100));
	m_circleMousePos.setOrigin(m_circleMousePos.getRadius(), m_circleMousePos.getRadius());

	m_blackHole.setRadius(60);
	m_blackHole.setPosition(windowSize.x / 2, 200);
	m_blackHole.setOrigin(m_blackHole.getRadius(), m_blackHole.getRadius());

	m_hitBlackHolePoint.setRadius(10);
	m_hitBlackHolePoint.setFillColor(sf::Color::Red);
	m_hitBlackHolePoint.setOrigin(m_hitBlackHolePoint.getRadius(), m_hitBlackHolePoint.getRadius());

	// ---- Convex shapes
	m_convexShapeStatic.setPointCount(m_baseShape1.size());
	for (int i = 0; i < static_cast<int>(m_convexShapeStatic.getPointCount()); ++i)
	{
		m_convexShapeStatic.setPoint(i, m_baseShape1[i]);
	}

	m_convexShapeMousePos.setPointCount(m_baseShape2.size());
	for (int i = 0; i < static_cast<int>(m_convexShapeMousePos.getPointCount()); ++i)
	{
		m_convexShapeMousePos.setPoint(i, m_baseShape2[i]);
	}

	constexpr float CONVEX_SHAPES_SIZE = 10.f;

	m_convexShapeStatic.setScale(CONVEX_SHAPES_SIZE, CONVEX_SHAPES_SIZE);
	m_convexShapeMousePos.setScale(CONVEX_SHAPES_SIZE, CONVEX_SHAPES_SIZE);

	m_convexShapeMousePos.setFillColor(sf::Color(0, 0, 255, 150));

	m_convexShapeStatic.setPosition(200, 400);
	m_convexShapeMousePos.setPosition(200, 400);

	// ---- Terrain
	m_terrain->generateTerrain(windowSize);
}

void MainGameScene::update(const float& deltaTime)
{
	IScene::update(deltaTime);

	// ---- Terrain hit test
	m_circleMousePos.setPosition(static_cast<sf::Vector2f>(getMousePositionWindow()));

	updateSkyColor(m_terrain->IsHit() ? GameColors::sweetPink : GameColors::sky);

	// ---- Circle circle hit test
	CollisionUtils::HitResult hitResult;
	const bool hitCircleCircleDebug = CollisionUtils::circleToCircle(
		m_circleMousePos.getPosition(), m_circleMousePos.getRadius(), 
		m_blackHole.getPosition(), m_blackHole.getRadius(), 
		hitResult);

	m_blackHole.setFillColor(hitCircleCircleDebug ? GameColors::smoothPurple : GameColors::nightPurple);
	m_hitBlackHolePoint.setPosition(hitResult.impactPoint);

	if(hitCircleCircleDebug)
	{
		std::cout << "Normal circle hit: " << VectorUtils::ToString(hitResult.normal) << std::endl;
	}

	// ---- Convex shape hit test
	//m_convexShapeMousePos.setPosition(static_cast<sf::Vector2f>(getMousePositionWindow()));
	m_convexShapeStatic.rotate(10.f * deltaTime);

	std::vector<sf::Vector2f> convexShapeEdgesStatic;
	for (const auto& edge : m_baseShape1)
	{
		convexShapeEdgesStatic.emplace_back(m_convexShapeStatic.getTransform().transformPoint(edge));
	}

	std::vector<sf::Vector2f> convexShapeEdgesMouse;
	for (const auto& edge : m_baseShape2)
	{
		convexShapeEdgesMouse.emplace_back(m_convexShapeMousePos.getTransform().transformPoint(edge));
	}

	const bool hitPolyDebug = CollisionUtils::polygonToPolygon(convexShapeEdgesStatic, convexShapeEdgesMouse);

	m_convexShapeStatic.setFillColor(hitPolyDebug ? sf::Color::Red : GameColors::dirty);
}

void MainGameScene::render()
{
	m_window.draw(m_background);

	IScene::render();

	m_window.draw(m_blackHole);
	m_window.draw(m_hitBlackHolePoint);

	m_window.draw(m_convexShapeStatic);

	m_window.draw(m_convexShapeMousePos);
	m_window.draw(m_circleMousePos);
}

void MainGameScene::updateSkyColor(const sf::Color& color)
{
	m_background.setFillColor(color);
}
