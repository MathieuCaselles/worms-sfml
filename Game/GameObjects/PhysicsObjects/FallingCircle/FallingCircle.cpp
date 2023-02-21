#include "FallingCircle.h"

#include <utility>

FallingCircle::FallingCircle()
	: FallingCircle(sf::CircleShape(), {})
{ }

FallingCircle::FallingCircle(sf::CircleShape circleShape, const PhysicsProperties& properties)
	: FallingCircle(std::move(circleShape), properties, circleShape.getPosition(), circleShape.getRotation())

{ }

FallingCircle::FallingCircle(sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation)
	: GameObject<PCFallingCircle, GCFallingCircle, ICVoid>(),
	CircleRigidBody(m_circleShape, properties),
	m_circleShape(std::move(circleShape))
{
	m_rbPosition = initialPosition;
	m_rbRotation = initialRotation;

	m_circleShape.setPosition(m_rbPosition);
	m_circleShape.setRotation(m_rbRotation);
}
