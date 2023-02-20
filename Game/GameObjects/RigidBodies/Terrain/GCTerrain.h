#pragma once

#include <Engine/Components/GraphicsComponent.h>

class TerrainRB;

struct GCTerrain : Engine::IGraphicsComponent
{
	GCTerrain() = default;
	
	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};
