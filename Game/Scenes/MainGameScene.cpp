#include "MainGameScene.h"

#include "Engine/Game/Game.h"
#include "Engine/Utility/VectorUtils.h"
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
	m_convexShapeStatic.setPosition(400, 200);

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
	CollisionUtils::HitResult ccHitResult;
	const bool hitCircleCircleDebug = CollisionUtils::circleToCircle(
		m_circleMousePos.getPosition(), m_circleMousePos.getRadius(), 
		m_blackHole.getPosition(), m_blackHole.getRadius(), 
		ccHitResult);

	m_blackHole.setFillColor(hitCircleCircleDebug ? GameColors::smoothPurple : GameColors::nightPurple);

	if(hitCircleCircleDebug)
	{
		m_hitBlackHolePoint.setPosition(ccHitResult.impactPoint);
		std::cout << "Normal circle hit: " << VectorUtils::ToString(ccHitResult.normal) << std::endl;
	}

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

	m_convexShapeMousePos.setOutlineColor(hitPolyDebug ? sf::Color::Blue : sf::Color(0, 255, 0, 150));

	if(hitPolyDebug)
	{
		// std::cout << "Normal poly hit: " << VectorUtils::ToString(ppHitResult.normal) << std::endl;
	}

	// ---- Polygon - Circle hit test
	CollisionUtils::HitResult pcHitResult;
	const bool hitCirclePolyDebug = CollisionUtils::polygonToCircle(convexShapeEdgesStatic, m_circleMousePos.getPosition(), m_circleMousePos.getRadius(), pcHitResult);

	m_circleMousePos.setFillColor(hitCirclePolyDebug ? sf::Color::Blue : sf::Color(0, 255, 0, 150));

	if(hitCirclePolyDebug)
	{
		std::cout << "Normal circle-poly hit: " << VectorUtils::ToString(pcHitResult.normal) << std::endl;
	}
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
