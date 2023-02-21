#include "IRigidBody.h"

#include "Engine/Utility/VectorUtils.h"

void IRigidBody::step(const float& deltaTime)
{
	for (const auto& force : m_forces)
	{
		m_rbVelocity += force * deltaTime;
	}

	if(!m_rbProperties.m_isStatic)
	{
		m_rbPosition += m_rbVelocity;
	}

	m_forces.clear();
}

IRigidBody::IRigidBody(const PhysicsProperties& properties)
	: m_rbProperties(properties) { }
