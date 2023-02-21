#include "CircleRigidBody.h"

#include "Engine/Utility/MathUtils.h"

CircleRigidBody::CircleRigidBody(sf::CircleShape& circleShape, const PhysicsProperties& properties)
	: IRigidBody(properties),
	  m_circleShape(circleShape)
{
	if(m_rbProperties.m_mass < 0.0001f)
	{
		const float surfaceArea = m_circleShape.getRadius() * m_circleShape.getRadius() * MathUtils::PI;
		m_rbProperties.m_mass = surfaceArea * m_rbProperties.m_density;
	}
}

void CircleRigidBody::step(const float& deltaTime)
{
	IRigidBody::step(deltaTime);
}