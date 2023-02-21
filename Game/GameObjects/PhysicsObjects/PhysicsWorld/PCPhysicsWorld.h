#pragma once

#include <Engine/Components/PhysicsComponent.h>

#include "Engine/Utility/CollisionUtils.h"

class IRigidBody;

struct PCPhysicsWorld : Engine::IPhysicsComponent
{
	PCPhysicsWorld() = default;
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;

	static bool collide(IRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& hitResult);
};
