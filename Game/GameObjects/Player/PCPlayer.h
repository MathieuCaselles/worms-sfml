#pragma once

#include <Engine/Components/PhysicsComponent.h>

class PCPlayer : Engine::IPhysicsComponent
{
	PCPlayer() = default;
	void updateImplementation(const float& deltaTime, Engine::IGameObject & gameObject, Engine::IScene & scene) override;
};