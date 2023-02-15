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

	m_background.setSize(static_cast<sf::Vector2f>(m_window.getSize()));

	m_mousePosCircle.setRadius(TERRAIN_DEBUG_MOUSE_RADIUS);
	m_mousePosCircle.setFillColor(sf::Color(0, 255, 0, 150));
	m_mousePosCircle.setOrigin(m_mousePosCircle.getRadius(), m_mousePosCircle.getRadius());

	m_terrain->generateTerrain(static_cast<sf::Vector2f>(m_window.getSize()));
}

void MainGameScene::update(const float& deltaTime)
{
	IScene::update(deltaTime);

	m_mousePosCircle.setPosition(static_cast<sf::Vector2f>(getMousePositionWindow()));

	updateSkyColor(m_terrain->IsHit() ? GameColors::sweetPink : GameColors::sky);
}

void MainGameScene::render()
{
	m_window.draw(m_background);

	IScene::render();

	m_window.draw(m_mousePosCircle);
}

void MainGameScene::updateSkyColor(const sf::Color& color)
{
	m_background.setFillColor(color);
}
