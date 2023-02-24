#pragma once

#include <Engine/Components/PhysicsComponent.h>

struct PCFallingCircle : Engine::IPhysicsComponent
{
	PCFallingCircle() = default;
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};