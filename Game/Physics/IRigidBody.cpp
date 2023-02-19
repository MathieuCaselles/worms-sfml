#include "IRigidBody.h"

#include <iostream>

#include "Engine/Utility/VectorUtils.h"

void IRigidBody::step(const float& deltaTime)
{
	m_rbPosition += m_rbVelocity * deltaTime;
	m_rbRotation += m_rbAngularVelocity * deltaTime;

	std::cout << VectorUtils::ToString(m_rbPosition) << std::endl;
}

IRigidBody::IRigidBody(const PhysicsProperties& properties)
	: m_rbProperties(properties) { }
