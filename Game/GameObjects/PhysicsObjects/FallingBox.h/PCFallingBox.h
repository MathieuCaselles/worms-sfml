#pragma once

#include <Engine/Components/PhysicsComponent.h>

struct PCFallingBox : Engine::IPhysicsComponent
{
	PCFallingBox() = default;
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};