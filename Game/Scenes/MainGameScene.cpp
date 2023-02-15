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
	m_background.setFillColor(GameColors::sky);

	m_terrain->generateTerrain(static_cast<sf::Vector2f>(m_window.getSize()));
}

void MainGameScene::render()
{
	m_window.draw(m_background);

	IScene::render();
}
