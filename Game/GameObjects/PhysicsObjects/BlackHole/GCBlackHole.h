#pragma once

#include "Engine/GameObject/GameObject.h"

struct GCBlackHole : Engine::IGraphicsComponent
{
	GCBlackHole() = default;

	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};