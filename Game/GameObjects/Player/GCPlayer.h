#pragma once

#include "Engine/GameObject/GameObject.h"

struct GCPlayer : Engine::IGraphicsComponent
{
	GCPlayer() = default;

	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};