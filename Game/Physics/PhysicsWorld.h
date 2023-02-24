#pragma once

#include "Engine/Utility/CollisionUtils.h"

class IRigidBody;

class PhysicsWorld
{

public:
	inline static const sf::Vector2f GRAVITY_FORCE{ 0, 9.81f };

public:
	void step(const float& deltaTime) const;
	static bool collide(IRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& hitResult);

	void addRigidBody(IRigidBody& rb);
	void removeRigidBody(IRigidBody& rb);

	[[nodiscard]] const std::vector<IRigidBody*>& getAllRigidBodies() const { return m_rigidBodies; }

private:
	std::vector<IRigidBody*> m_rigidBodies;
};
