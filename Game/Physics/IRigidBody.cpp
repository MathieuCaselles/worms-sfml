#include "IRigidBody.h"

#include "Engine/Utility/VectorUtils.h"

void IRigidBody::step(const float& deltaTime)
{
	addMovement(m_rbVelocity * deltaTime);
}

IRigidBody::IRigidBody(const PhysicsProperties& properties)
	: m_rbProperties(properties) { }
