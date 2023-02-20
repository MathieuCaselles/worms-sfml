#pragma once

#include <Engine/Components/PhysicsComponent.h>

struct PCTerrain : Engine::IPhysicsComponent
{
	PCTerrain();
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};