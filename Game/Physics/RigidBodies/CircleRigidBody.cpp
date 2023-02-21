#include "CircleRigidBody.h"

#include "Engine/Utility/MathUtils.h"

CircleRigidBody::CircleRigidBody(sf::CircleShape& circleShape, const PhysicsProperties& properties)
	: IRigidBody(properties),
	  m_circleShape(circleShape)
{ }

void CircleRigidBody::step(const float& deltaTime)
{
	IRigidBody::step(deltaTime);

	m_circleShape.setPosition(m_rbPosition);
	m_circleShape.setRotation(m_rbRotation);
}

void CircleRigidBody::updateMass()
{
	const float surfaceArea = m_circleShape.getRadius() * m_circleShape.getRadius() * MathUtils::PI;
	m_rbProperties.m_mass = surfaceArea * m_rbProperties.m_density;

	IRigidBody::updateMass();
}
