#include "CircleRigidBody.h"

#include "Engine/Utility/MathUtils.h"

CircleRigidBody::CircleRigidBody(const sf::CircleShape& circleCollisionShape, const PhysicsProperties& properties)
	: IRigidBody(properties),
	  m_circleCollisionShape(circleCollisionShape)
{
	m_circleCollisionShape.setFillColor(sf::Color(0, 0, 0, 0));
	m_circleCollisionShape.setOutlineColor(sf::Color(0, 0, 0, 0));

	m_circleCollisionShape.setOrigin(circleCollisionShape.getRadius(), circleCollisionShape.getRadius());
}

void CircleRigidBody::step(const float& deltaTime)
{
	IRigidBody::step(deltaTime);

	m_circleCollisionShape.setPosition(m_rbPosition);
	m_circleCollisionShape.setRotation(m_rbRotation);
}

void CircleRigidBody::updateMass()
{
	const float surfaceArea = m_circleCollisionShape.getRadius() * m_circleCollisionShape.getRadius() * MathUtils::PI * PHYSICS_UNIT_METER_PER_PIXEL;
	m_rbProperties.m_mass = surfaceArea * m_rbProperties.m_density;

	IRigidBody::updateMass();
}
