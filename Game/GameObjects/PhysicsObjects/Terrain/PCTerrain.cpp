#include "PCTerrain.h"

#include "Terrain.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Utility/VectorUtils.h"

PCTerrain::PCTerrain()
{ }

void PCTerrain::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& terrain = reinterpret_cast<Terrain&>(gameObject);

}