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

	m_mousePosCircle.setRadius(TERRAIN_DEBUG_MOUSE_RADIUS);
	m_mousePosCircle.setFillColor(sf::Color(0, 255, 0, 150));
	m_mousePosCircle.setOrigin(m_mousePosCircle.getRadius(), m_mousePosCircle.getRadius());

	m_blackHole.setRadius(60);
	m_blackHole.setPosition(windowSize.x / 2, 200);
	m_blackHole.setOrigin(m_blackHole.getRadius(), m_blackHole.getRadius());

	m_hitBlackHolePoint.setRadius(10);
	m_hitBlackHolePoint.setFillColor(sf::Color::Red);
	m_hitBlackHolePoint.setOrigin(m_hitBlackHolePoint.getRadius(), m_hitBlackHolePoint.getRadius());

	m_terrain->generateTerrain(windowSize);
}

void MainGameScene::update(const float& deltaTime)
{
	IScene::update(deltaTime);

	// Terrain hit test
	m_mousePosCircle.setPosition(static_cast<sf::Vector2f>(getMousePositionWindow()));

	updateSkyColor(m_terrain->IsHit() ? GameColors::sweetPink : GameColors::sky);

	// Circle circle hit test
	CollisionUtils::HitResult hitResult;
	const bool hitCircleCircleDebug = CollisionUtils::circleToCircle(
		m_mousePosCircle.getPosition(), m_mousePosCircle.getRadius(), 
		m_blackHole.getPosition(), m_blackHole.getRadius(), 
		hitResult);

	m_blackHole.setFillColor(hitCircleCircleDebug ? GameColors::smoothPurple : GameColors::nightPurple);
	m_hitBlackHolePoint.setPosition(hitResult.impactPoint);
}

void MainGameScene::render()
{
	m_window.draw(m_background);

	IScene::render();

	m_window.draw(m_blackHole);
	m_window.draw(m_hitBlackHolePoint);

	m_window.draw(m_mousePosCircle);
}

void MainGameScene::updateSkyColor(const sf::Color& color)
{
	m_background.setFillColor(color);
}
