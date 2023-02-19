#pragma once

#include "Engine/GameObject/GameObject.h"

struct GCFallingBox : Engine::IGraphicsComponent
{
	GCFallingBox() = default;

	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};