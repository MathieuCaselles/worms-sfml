#include "MainGameScene.h"


#include <Game/GameObjects/UI/Buttons/Button.h>

#include "Engine/Game/Game.h"
#include "Game/Assets/GameColors.h"

MainGameScene::MainGameScene()
{
	// TODO : Put a getter of window size instead of hard coding the supposed window size
	const auto windowSize = sf::Vector2f(1920, 1080);

	_background.setSize(windowSize);
	_background.setFillColor(GameColors::_sky);

	addGameObjects(new Terrain(windowSize));
}

void MainGameScene::render()
{
	m_window.draw(_background);

	IScene::render();
}