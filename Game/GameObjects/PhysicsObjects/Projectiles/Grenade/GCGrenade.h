#pragma once

#include "Engine/GameObject/GameObject.h"

struct GCGrenade : Engine::IGraphicsComponent
{
	GCGrenade() = default;

	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};
