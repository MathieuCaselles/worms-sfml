#pragma once

#include <Engine/Components/PhysicsComponent.h>

struct PCCircleExplosion : Engine::IPhysicsComponent
{
	PCCircleExplosion() = default;
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};
