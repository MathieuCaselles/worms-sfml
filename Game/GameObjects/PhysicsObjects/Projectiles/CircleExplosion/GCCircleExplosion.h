#pragma once

#include "Engine/GameObject/GameObject.h"

struct GCCircleExplosion : Engine::IGraphicsComponent
{
	GCCircleExplosion() = default;

	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};
