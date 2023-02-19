#pragma once

#include "Game/Physics/IRigidBody.h"

class CircleRigidBody : public IRigidBody
{
	CircleRigidBody(float circleRadius, const PhysicsProperties& properties);

	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};
