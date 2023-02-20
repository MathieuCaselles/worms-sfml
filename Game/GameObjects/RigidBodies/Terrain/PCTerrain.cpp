#include "PCTerrain.h"

#include "TerrainRB.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Utility/VectorUtils.h"

PCTerrain::PCTerrain()
{ }

void PCTerrain::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& terrain = reinterpret_cast<TerrainRB&>(gameObject);

	const auto mousePosition = static_cast<sf::Vector2f>(scene.getMousePositionScreen());
}