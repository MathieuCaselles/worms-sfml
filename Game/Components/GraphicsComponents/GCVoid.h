#pragma once

#include <Engine/Components/GraphicsComponent.h>

struct GCVoid : Engine::IGraphicsComponent
{
	GCVoid();
	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};

