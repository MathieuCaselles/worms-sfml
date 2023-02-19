#pragma once

#include "Game/Physics/IRigidBody.h"

class BoxRigidBody : public IRigidBody
{
	BoxRigidBody(const sf::Vector2f& boxBounds, const PhysicsProperties& properties);

	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;
};
