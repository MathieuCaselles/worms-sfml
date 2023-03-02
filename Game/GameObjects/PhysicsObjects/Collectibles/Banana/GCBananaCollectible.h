#pragma once

#include "Engine/GameObject/GameObject.h"

struct GCBananaCollectible : Engine::IGraphicsComponent
{
	GCBananaCollectible() = default;

	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};
