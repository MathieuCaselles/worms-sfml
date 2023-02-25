#pragma once

#include <Engine/Components/PhysicsComponent.h>

class IRigidBody;

struct PCForceVolume : Engine::IPhysicsComponent
{
	PCForceVolume() = default;
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};
