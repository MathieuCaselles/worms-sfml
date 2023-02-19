#pragma once

#include <Engine/Components/PhysicsComponent.h>

struct PCPhysicsWorld : Engine::IPhysicsComponent
{
	PCPhysicsWorld();
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};