#include "MainGameScene.h"

#include "Engine/Game/Game.h"
#include "Game/Assets/GameColors.h"
#include "Game/GameObjects/Terrain/Terrain.h"

MainGameScene::MainGameScene()
{
	_terrain = std::make_unique<Terrain>();
	addGameObjects(_terrain.get());
}

void MainGameScene::onBeginPlay()
{
	IScene::onBeginPlay();

	_background.setSize(static_cast<sf::Vector2f>(m_window.getSize()));
	_background.setFillColor(GameColors::_sky);

	_terrain->generateTerrain(static_cast<sf::Vector2f>(m_window.getSize()));
}

void MainGameScene::render()
{
	m_window.draw(_background);

	IScene::render();
}
