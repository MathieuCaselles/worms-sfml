#pragma once

#include "Engine/GameObject/GameObject.h"

struct GCFallingCircle : Engine::IGraphicsComponent
{
	GCFallingCircle() = default;

	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};