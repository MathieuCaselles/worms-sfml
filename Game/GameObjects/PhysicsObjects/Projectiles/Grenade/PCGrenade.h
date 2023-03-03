#pragma once

#include <Engine/Components/PhysicsComponent.h>

struct PCGrenade : Engine::IPhysicsComponent
{
	PCGrenade() = default;
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};