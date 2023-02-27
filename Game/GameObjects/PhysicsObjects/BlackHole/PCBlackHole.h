#pragma once

#include <Engine/Components/PhysicsComponent.h>

class IRigidBody;

struct PCBlackHole : Engine::IPhysicsComponent
{
	PCBlackHole() = default;
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};
