#include "BlackHole.h"

#include "Game/Physics/PhysicsProperties.h"

BlackHole::BlackHole(const sf::CircleShape& circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float centerAttractionForce)
	: GameObject<PCBlackHole, GCBlackHole, ICVoid>(),
	CircleRigidBody(circleShape, properties),
	m_blackHoleShape(circleShape),
	m_centerAttractionForce(centerAttractionForce)
{
	CircleRigidBody::updateMass();

	m_rbPosition = initialPosition;

	m_blackHoleShape.setPosition(m_rbPosition);
	m_blackHoleShape.setRotation(m_rbRotation);
}

void BlackHole::setCenterAttractionForce(float force)
{
	m_centerAttractionForce = force;
}

float BlackHole::getCenterAttractionForce() const
{
	return m_centerAttractionForce;
}
