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

void IRigidBody::addForce(const sf::Vector2f& force)
{
	m_forces.push_back(force / m_rbProperties.m_mass); // a = F / m
}

void IRigidBody::updateMass()
{
	m_rbProperties.m_invMass = !m_rbProperties.m_isStatic ? 1.f / m_rbProperties.m_mass : 0.f;
}

void IRigidBody::translate(const sf::Vector2f& movementVector)
{
	if (!m_rbProperties.m_isStatic)
	{
		m_rbPosition += movementVector;
	}
}

IRigidBody::IRigidBody(const PhysicsProperties& properties)
	: m_rbProperties(properties) { }